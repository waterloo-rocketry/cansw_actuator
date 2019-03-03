#include <stdio.h>
#include <stdlib.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"

#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/pin_manager.h"

#include "vent.h"
#include "lin_actuator.h"
#include "timer.h"

#include <xc.h>

static void can_msg_handler(can_msg_t *msg);

// Follows VALVE_STATE in message_types.h
// SHOULD ONLY BE MODIFIED IN ISR
static uint8_t requested_valve_state = VALVE_OPEN;

lin_actuator_states vent_state = nominal;

int main(int argc, char** argv) {
    // MCC generated initializer
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();
    
    FVR_Initialize();
    ADCC_Initialize();
    ADCC_DisableContinuousConversion();

    // I2C1 Pins: SCL1 -> RC3, SDA1 -> RC4
    I2C1_Initialize();  
    LED_init();
    
    // init our millisecond function
    timer0_init();
    
    // Enable global interrupts
    INTCON0bits.GIE = 1;
    
    // Set up CAN TX
    TRISC0 = 0;
    RC0PPS = 0x33;
    
    // Set up CAN RX
    TRISC1 = 1;
    ANSELC1 = 0;
    CANRXPPS = 0x11;
    
    // set up CAN module
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);
    can_init(&can_setup, can_msg_handler);
    
    // Set up linear actuator
    lin_actuator_init();
    lin_actuator_dac_init();
    
    close_vent();
    while (1) {
        BLUE_LED_OFF();
        __delay_ms(100);
        BLUE_LED_ON();
        __delay_ms(100);
        
        // check for general board status
        bool status_ok = true;
        status_ok &= check_battery_voltage();
        status_ok &= check_bus_voltage();
        status_ok &= check_bus_current();
        status_ok &= check_valve_status();
        
        // if there was an issue, a message would already have been sent out
        if (status_ok) { send_status_ok(); }

        // For debugging purposes, put the valve state on the white LED
        switch (requested_valve_state) {
            case VALVE_OPEN:
                WHITE_LED_ON();
                break;
            case VALVE_CLOSED:
                WHITE_LED_OFF();
                break;
            default:
                break;
        }
        
        
        vent_state = check_vent_status();
    }
    
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

static void can_msg_handler(can_msg_t *msg) {
    uint16_t msg_type = get_message_type(msg);
    switch (msg_type) {
        case MSG_GENERAL_CMD:
            // nothing right now
            break;

        case MSG_VENT_VALVE_CMD:
            // see message_types.h for message format
            // vent position will be updated synchronously
            requested_valve_state = msg->data[3];
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

        // all the other ones - do nothing
        case MSG_INJ_VALVE_CMD:
        case MSG_DEBUG_MSG:
        case MSG_DEBUG_PRINTF:
        case MSG_VENT_VALVE_STATUS:
        case MSG_INJ_VALVE_STATUS:
        case MSG_SENSOR_ACC:
        case MSG_SENSOR_GYRO:
        case MSG_SENSOR_MAG:
        case MSG_SENSOR_ANALOG:
        case MSG_GENERAL_BOARD_STATUS:
            break;

        // illegal message type - should never get here
        default:
            // send a message or something
            break;
    }
    
    // keep track of heartbeat here
}
