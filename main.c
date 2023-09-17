#include <stdio.h>
#include <stdlib.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/pin_manager.h"

#include "actuator.h"
#include "board.h"
#include "error_checks.h"
#include "timer.h"

#include <xc.h>

static void can_msg_handler(const can_msg_t *msg);
static void send_status_ok(void);

// Follows ACTUATOR_STATE in message_types.h
// SHOULD ONLY BE MODIFIED IN ISR
volatile enum ACTUATOR_STATE requested_actuator_state = SAFE_STATE;

// flags for if we have seen can messages and valid commands for different timeouts
// bools so that the ISR only has to write a single byte and is thus atomic
volatile bool seen_can_message = false;
volatile bool seen_can_command = false;

//memory pool for the CAN tx buffer
uint8_t tx_pool[100];

int main(int argc, char** argv) {
    // MCC generated initializer
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();

    FVR_Initialize();
    ADCC_Initialize();
    ADCC_DisableContinuousConversion();

    LED_init();

    // init our millisecond function
    timer0_init();

    // Enable global interrupts
    INTCON0bits.GIE = 1;

    // Set up CAN TX
    TRISC1 = 0;
    RC1PPS = 0x33;

    // Set up CAN RX
    TRISC0 = 1;
    ANSELC0 = 0;
    CANRXPPS = 0x10;

    // set up CAN module
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);
    can_init(&can_setup, can_msg_handler);
    // set up CAN tx buffer
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    // loop timer
    uint32_t last_millis = millis();
    uint32_t last_command_millis = millis();
    uint32_t last_message_millis = millis();

    // Set up actuator
    actuator_init();

    bool blue_led_on = false;   // visual heartbeat
    while (1) {
        CLRWDT(); // feed the watchdog, which is set for 256ms
        
        if (OSCCON2 != 0x70) { // If the fail-safe clock monitor has triggered
            OSCILLATOR_Initialize();
        }
        
        if (seen_can_message) {
            seen_can_message = false;
            last_message_millis = millis();
        }
        if (seen_can_command) {
            seen_can_command = false;
            last_command_millis = millis();
        }
        
        if (millis() - last_message_millis > MAX_BUS_DEAD_TIME_ms &&
            (SAFE_STATE_ENABLED || requested_actuator_state == SAFE_STATE)) {
            // Only reset if safe state is enabled (aka this isn't injector valve)
            // OR this is injector valve and the currently requested state is the safe
            // state (closed)
            
            // We've got too long without seeing a valid CAN message (including one of ours)
            RESET();
        }
        
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_ms) {

            // check for general board status
            bool status_ok = true;
            status_ok &= check_battery_voltage_error();
            status_ok &= check_bus_current_error();
            status_ok &= check_actuator_pin_error(requested_actuator_state);

            // if there was an issue, a message would already have been sent out
            if (status_ok) { send_status_ok(); }

            // Set safe state if:
            // 1. We haven't heard CAN traffic in a while
            // 2. We're low on battery voltage
            // "thread safe" because main loop should never write to requested_actuator_state
            if (SAFE_STATE_ENABLED && (
                    (millis() - last_command_millis > MAX_CAN_IDLE_TIME_MS)
                    || is_batt_voltage_critical())) {
                actuator_send_status(SAFE_STATE);
                actuator_set(SAFE_STATE);
            } else {
                actuator_send_status(requested_actuator_state);
                actuator_set(requested_actuator_state);
            }

            // visual heartbeat indicator
            if (blue_led_on) {
                BLUE_LED_OFF();
                blue_led_on = false;
            } else {
                BLUE_LED_ON();
                blue_led_on = true;
            }

            // update our loop counter
            last_millis = millis();
        }
        //send any queued CAN messages
        txb_heartbeat();
    }

    // unreachable
    return (EXIT_SUCCESS);
}

static void interrupt interrupt_handler() {
    if (PIR5) {
        can_handle_interrupt();
    }

    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}

static void can_msg_handler(const can_msg_t *msg) {
    seen_can_message = true;
    
    uint16_t msg_type = get_message_type(msg);

    // declare this in advance cause we can't declare it inside the switch
    // and I don't want to replace this entire thing with an ifelse
    int cmd_type = -1;
    int dest_id = -1;

    // ignore messages that were sent from this board
    if (get_board_unique_id(msg) == BOARD_UNIQUE_ID) {
        return;
    }

    switch (msg_type) {
        case MSG_GENERAL_CMD:
            cmd_type = get_general_cmd_type(msg);
            if (cmd_type == BUS_DOWN_WARNING) {
                requested_actuator_state = SAFE_STATE;
            }
            break;

        case MSG_ACTUATOR_CMD:
            // see message_types.h for message format
            if (get_actuator_id(msg) == ACTUATOR_ID) {
                // vent position will be updated synchronously
                requested_actuator_state = get_req_actuator_state(msg);
                // keep track of heartbeat here
                seen_can_command = true;
            }

            break;

        case MSG_LEDS_ON:
            RED_LED_ON();
            BLUE_LED_ON();
            WHITE_LED_ON();
            break;

        case MSG_LEDS_OFF:
            RED_LED_OFF();
            BLUE_LED_OFF();
            WHITE_LED_OFF();
            break;
        
        case MSG_RESET_CMD:
            dest_id = get_reset_board_id(msg);
            if (dest_id == BOARD_UNIQUE_ID || dest_id == 0 ){
                RESET();
            }
            break;

        // all the other ones - do nothing
        default:
            break;
    }
}

// Send a CAN message with nominal status
static void send_status_ok(void) {
    can_msg_t board_stat_msg;
    build_board_stat_msg(millis(), E_NOMINAL, NULL, 0, &board_stat_msg);

    // send it off at low priority
    txb_enqueue(&board_stat_msg);
}
