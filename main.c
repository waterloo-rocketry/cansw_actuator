#include <stdio.h>
#include <stdlib.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"

// MCC Generated I2C Driver
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"

#include "timer.h"

#include <xc.h>

#define _XTAL_FREQ 1000000

#define RED_LED_ON() (LATC5 = 0)
#define RED_LED_OFF() (LATC5 = 1)
#define WHITE_LED_ON() (LATC6 = 0)
#define WHITE_LED_OFF() (LATC6 = 1)
#define BLUE_LED_ON() (LATC7 = 0)
#define BLUE_LED_OFF() (LATC7 = 1)

static void can_msg_handler(can_msg_t *msg);
static void send_status_ok(void);

// Follows VALVE_STATE in message_types.h
// SHOULD ONLY BE MODIFIED IN ISR
static uint8_t requested_valve_state = VALVE_OPEN;

static void LED_init() {
    TRISC5 = 0;
    LATC5 = 1;      // turn the led off
    
    TRISC6 = 0;
    LATC6 = 1;      // turn the led off
    
    TRISC7 = 0;
    LATC7 = 1;      // turn the led off
}

int main(int argc, char** argv) {
    // MCC generated initializer
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();
    
    // I2C1 Pins: SCL1 -> RC3, SDA1 -> RC4
    I2C1_Initialize();  
    LED_init();
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
    can_setup.brp = 0;
    can_setup.sjw = 3;
    can_setup.btlmode = 0x01;
    can_setup.sam = 0;
    can_setup.seg1ph = 0x04;
    can_setup.prseg = 0;
    can_setup.seg2ph = 0x04;
    can_init(&can_setup, can_msg_handler);
    
    while (1){
        BLUE_LED_OFF();
        __delay_ms(100);
        BLUE_LED_ON();
        __delay_ms(100);
        
        send_status_ok();
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
}

// Send a CAN message with nominal status
static void send_status_ok(void) {
    can_msg_t board_stat_msg;
    board_stat_msg.sid = MSG_GENERAL_BOARD_STATUS | BOARD_UNIQUE_ID;

    // capture the most recent timestamp
    uint32_t last_millis = millis();

    // paste in the timestamp one byte at a time. Most significant byte goes in data[0].
    board_stat_msg.data[0] = (last_millis >> 16) & 0xff;
    board_stat_msg.data[1] = (last_millis >> 8) & 0xff;
    board_stat_msg.data[2] = (last_millis >> 0) & 0xff;

    // set the error code
    board_stat_msg.data[3] = E_NOMINAL;

    // 3 byte timestamp + 1 byte error code
    board_stat_msg.data_len = 4;

    // send it off at low priority
    can_send(&board_stat_msg, 0);
}

