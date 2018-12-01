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
#define HIGH_DAC_ADDRESS 0x4d
#define LOW_DAC_ADDRESS 0x4c

static void LED_init() {
    TRISC5 = 0;
    LATC5 = 1;      // turn the led off
    
    TRISC6 = 0;
    LATC6 = 1;      // turn the led off
    
    TRISC7 = 0;
    LATC7 = 1;      // turn the led off
}
const uint8_t highVal = 200;
const uint8_t lowVal = 50;
uint8_t byte1 = 0x00, byte2 = 0x00;
uint8_t* b1 = &byte1, b2 = &byte2;

void analogValToData(uint8_t value, uint8_t* B1, uint8_t* B2){
   *B1 = ((value & 0xf0) >> 4); // shift the 4 MSB to the 4 LSB
   *B2 = ((value & 0x0f) << 4); // mask the 4MSB then shift the 4 LSB to the 4MSB
}

int main(int argc, char** argv) {
    // MCC generated initializer
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();
    
    // I2C1 Pins: SCL1 -> RC3, SDA1 -> RC4
    I2C1_Initialize();
    
    LED_init();
    
    // Set DACs
    analogValToData(highVal, b1, b2);
    i2c1_write2Bytes(HIGH_DAC_ADDRESS, byte1, byte2);
    analogValToData(lowVal, b1, b2);
    i2c1_write2Bytes(LOW_DAC_ADDRESS, byte1, byte2); 
    if(i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
            RED_LED_ON;
    
    while (1){
        BLUE_LED_ON;
        __delay_ms(500);
        BLUE_LED_OFF;
        __delay_ms(500);        
    }
    
    return (EXIT_SUCCESS);
}

