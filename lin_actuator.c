#include <xc.h>
#include<stdint.h>
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"
#include "lin_actuator.h"

// FIXME
#define RED_LED_ON() (LATC5 = 0)
#define RED_LED_OFF() (LATC5 = 1)

static lin_actuator_states moving = stopped;

void set_DACs(){
  uint8_t data_buf[2]; 
  data_buf[0] = ((HIGH_DAC_VAL & 0xf0) >> 4); // shift the 4 MSB to the 4 LSB
  data_buf[1] = ((HIGH_DAC_VAL & 0x0f) << 4); // mask the 4MSB then shift the 4 LSB to the 4MSB
  i2c1_writeNBytes(HIGH_DAC_ADDRESS, data_buf, 2);
  data_buf[0] = ((LOW_DAC_VAL & 0xf0) >> 4); // shift the 4 MSB to the 4 LSB
  data_buf[1] = ((LOW_DAC_VAL) << 4); // mask the 4MSB then shift the 4 LSB to the 4MSB
  i2c1_writeNBytes(LOW_DAC_ADDRESS, data_buf, 2); 
  if(i2c1_getLastError() == I2C1_FAIL_TIMEOUT){
        RED_LED_ON();
  }
}

 void lin_actuator_init() {
    TRISB1 = 0;     //set MOTOR_FWD as output
    LATB1 = 0;
    
    TRISB2 = 0;     //set MOTOR_BWD as output
    LATB2 = 0;
    
    TRISB3 = 1;     //set LIM_HIGH as input
    ANSELB3 = 0;    //set as digital input
    
    TRISB4 = 1;     //set LIM_LOW as input
    ANSELB4 = 0;    //set as digital input
    
    ANSELB5 = 1;
    TRISB5 = 1;
    
}
 
void open_vent(void){
    LATB1 = 0;      //FWD low
    LATB2 = 1;      //BWD high  
    moving = opening;
}
void close_vent(void){
    LATB2 = 0;      //BWD low
    LATB1 = 1;      //FWD high
    moving = closing;
}

lin_actuator_states check_vent_status(void){
    lin_actuator_states status = nominal;
    
    if(moving == opening){
        if(!RB4){
            LATB1 = 0;
            LATB2 = 0;
            moving = stopped;
        }
        else{
            status = opening;
        }
        
    }
    else if(moving == closing){
        if(!RB3){
            LATB1 = 0;
            LATB2 = 0;
            moving = stopped;
        }
        else{
            status = closing;
        }
    }
    else{
        if(RB3 && RB4){
          status = stopped_between_states; 
        }
    }
    if(!RB4){
            status = open;
    }
    if(!RB3){
            status = closed;
    }
    return status;
}