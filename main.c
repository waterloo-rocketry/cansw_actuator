#include <stdio.h>
#include <stdlib.h>

// MCC Generated I2C Driver
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"

#include <xc.h>

#define _XTAL_FREQ 1000000

#define RED_LED_ON (LATC5 = 0)
#define RED_LED_OFF (LATC5 = 1)
#define WHITE_LED_ON (LATC6 = 0)
#define WHITE_LED_OFF (LATC6 = 1)
#define BLUE_LED_ON (LATC7 = 0)
#define BLUE_LED_OFF (LATC7 = 1)

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
    
    while (1){
        BLUE_LED_ON;
        
        // I2C Demo - this isn't the real DAC address, so you won't get an ACK
        // Random Address: 0x20
        // Random Register: 0x10
        // Random Data: 0x55
        i2c1_write1ByteRegister(0x20, 0x10, 0x55);
        __delay_ms(500);
        BLUE_LED_OFF;
        __delay_ms(500);        
    }
    
    return (EXIT_SUCCESS);
}

