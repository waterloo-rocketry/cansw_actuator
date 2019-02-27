#include <stdio.h>
#include <stdlib.h>

// MCC Generated I2C Driver
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"

#include <xc.h>

#include "lin_actuator.h"

#define _XTAL_FREQ 1000000

#define RED_LED_ON (LATC5 = 0)
#define RED_LED_OFF (LATC5 = 1)
#define WHITE_LED_ON (LATC6 = 0)
#define WHITE_LED_OFF (LATC6 = 1)
#define BLUE_LED_ON (LATC7 = 0)
#define BLUE_LED_OFF (LATC7 = 1)
#define HIGH_DAC_ADDRESS 0x4d
#define LOW_DAC_ADDRESS 0x4c
#define HIGH_DAC_VAL 51 //from 0-255, multiply  desired voltage by 51
#define LOW_DAC_VAL 5
// global variables for debuging
int battery_voltage = 0;
int LINAC_POT = 0;
int current_draw = 0;
lin_actuator_states vent_state = nominal;

static void LED_init() {
    TRISC5 = 0;     //set C5 as output
    LATC5 = 1;      // turn the led off
    
    TRISC6 = 0;
    LATC6 = 1;      // turn the led off
    
    TRISC7 = 0;
    LATC7 = 1;      // turn the led off
}

void set_DACs(){
  uint8_t data_buf[2]; 
  data_buf[0] = ((HIGH_DAC_VAL & 0xf0) >> 4); // shift the 4 MSB to the 4 LSB
  data_buf[1] = ((HIGH_DAC_VAL & 0x0f) << 4); // mask the 4MSB then shift the 4 LSB to the 4MSB
  i2c1_writeNBytes(HIGH_DAC_ADDRESS, data_buf, 2);
  data_buf[0] = ((LOW_DAC_VAL & 0xf0) >> 4); // shift the 4 MSB to the 4 LSB
  data_buf[1] = ((LOW_DAC_VAL) << 4); // mask the 4MSB then shift the 4 LSB to the 4MSB
  i2c1_writeNBytes(LOW_DAC_ADDRESS, data_buf, 2); 
  if(i2c1_getLastError() == I2C1_FAIL_TIMEOUT){
        RED_LED_ON;
  }
}

int check_battery_voltage(void){    //returns mV
    return ADCC_GetSingleConversion(channel_VBAT)*3.95;
}

int check_current_draw(void){       //returns mA
    return ADCC_GetSingleConversion(channel_VSENSE)/20; //i =v/r r = 0.2 ohms, v = VSENCE/100
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
    lin_actuator_init();
    
    set_DACs();
    
    close_vent();
    while (1){
        battery_voltage = check_battery_voltage();// returns mV
        current_draw = check_current_draw();// returns mA
        LINAC_POT = ADCC_GetSingleConversion(channel_LINAC_POT);// returns mV
        
        vent_state = check_vent_status();
        /*
        if (vent_state == closed){
            __delay_ms(1000);
            open_vent();
        }
        else if(vent_state == open){
            __delay_ms(1000);
            close_vent();
        }
        */
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
    }
    
    return (EXIT_SUCCESS);
}

