#include <stdio.h>
#include <stdlib.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"

// MCC Generated I2C Driver
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"

#include <xc.h>

#define _XTAL_FREQ 1000000

#define RED_LED_ON() (LATC5 = 0)
#define RED_LED_OFF() (LATC5 = 1)
#define WHITE_LED_ON() (LATC6 = 0)
#define WHITE_LED_OFF() (LATC6 = 1)
#define BLUE_LED_ON() (LATC7 = 0)
#define BLUE_LED_OFF() (LATC7 = 1)

static void can_msg_handler(can_msg_t *msg);

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
        __delay_ms(50);
        BLUE_LED_ON();
        __delay_ms(50);
        
        can_msg_t msg;
        msg.sid = 0xa;
        msg.data_len = 0;
        can_send(&msg, 0);
    }
    
    return (EXIT_SUCCESS);
}

static void interrupt interrupt_handler() {
    if (PIR5) {
        RED_LED_ON();
        can_handle_interrupt();
    }
}

static void can_msg_handler(can_msg_t *msg) {
    // noop
    RED_LED_OFF();
}

