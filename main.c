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
#define GET_BATTERY_VOLTAGE ADCC_GetSingleConversion(RA0)
#define GET_CURRENT_DRAW ADCC_GetSingleConversion(RA1)
#define GET_BATTERY_VOLTAGE ADCC_GetSingleConversion(RB5)
#define HIGH_DAC_ADDRESS 0x4d
#define LOW_DAC_ADDRESS 0x4c
#define HIGH_VAL 50
#define LOW_VAL 3

int BatV = 0;

static void LED_init() {
    TRISC5 = 0;     //set C5 as output
    LATC5 = 1;      // turn the led off
    
    TRISC6 = 0;
    LATC6 = 1;      // turn the led off
    
    TRISC7 = 0;
    LATC7 = 1;      // turn the led off
}
static void LinAc_init() {
    TRISB1 = 0;     //set MOTOR_FWD as output
    LATB1 = 0;
    
    TRISB2 = 0;     //set MOTOR_BWD as output
    LATB2 = 0;
    
    TRISB3 = 1;     //set LIM_HIGH as input
    ANSELB3 = 0;    //set as digital input
    
    TRISB4 = 1;     //set LIM_LOW as input
    ANSELB4 = 0;    //set as digital input
}


void analogValToData(uint8_t value, uint8_t data_buf[2]){
   data_buf[0] = ((value & 0xf0) >> 4); // shift the 4 MSB to the 4 LSB
   data_buf[1] = ((value & 0x0f) << 4); // mask the 4MSB then shift the 4 LSB to the 4MSB
}
void setDACs(int lowVal, int highVal){
  uint8_t data_buf[2]; 
  analogValToData(HIGH_VAL, data_buf);
  i2c1_writeNBytes(HIGH_DAC_ADDRESS, data_buf, 2);
  analogValToData(LOW_VAL, data_buf);
  i2c1_writeNBytes(LOW_DAC_ADDRESS, data_buf, 2); 
  if(i2c1_getLastError() == I2C1_FAIL_TIMEOUT){
        RED_LED_ON;
  }
}

int openVent(){
    LATB1 = 1;      //FWD High
    LATB2 = 0;      //BWD Low
    
}
int closeVent(){
    LATB2 = 1;      //BWD High
    LATB1 = 0;      //FWD Low
}
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
    LinAc_init();
    
    // Set DACs
    setDACs(LOW_VAL, HIGH_VAL);
    
    closeVent();
    while (1){
        BatV = GET_BATTERY_VOLTAGE;
        if(RB4){
            WHITE_LED_ON;
        }
        else{
            WHITE_LED_OFF;
        }
        if(RB3){
            BLUE_LED_ON;
        }
        else{
            BLUE_LED_OFF;
        }  
        /*LATB1 = 1;      //FWD High
        LATB2 = 0;
        __delay_ms(1000);
        LATB1 = 0;     
        LATB2 = 1;
        __delay_ms(1000);
        LATB1 = 0;     
        LATB2 = 0;
        __delay_ms(1000);
        LATB1 = 1;     
        LATB2 = 1;
        __delay_ms(1000);
       */ 
    }
    
    return (EXIT_SUCCESS);
}

