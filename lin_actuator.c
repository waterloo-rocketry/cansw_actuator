#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"
#include "lin_actuator.h"
#include "vent.h"

bool lin_actuator_dac_init(void) {
  uint8_t data_buf[2]; 
  
  data_buf[0] = ((HIGH_DAC_VAL & 0xf0) >> 4);
  data_buf[1] = ((HIGH_DAC_VAL & 0x0f) << 4);
  i2c1_writeNBytes(HIGH_DAC_ADDRESS, data_buf, 2);
  
  data_buf[0] = ((LOW_DAC_VAL & 0xf0) >> 4);
  data_buf[1] = ((LOW_DAC_VAL & 0x0f) << 4);
  i2c1_writeNBytes(LOW_DAC_ADDRESS, data_buf, 2); 
  
  if(i2c1_getLastError() == I2C1_FAIL_TIMEOUT){
        return false;
  } else {
      // all is well
      return true;
  }
}

void lin_actuator_init(void) {
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
 
void vent_open(void) {
    WHITE_LED_ON();

    LATB1 = 0;      //FWD low
    LATB2 = 1;      //BWD high  
}

void vent_close(void) {
    WHITE_LED_OFF();

    LATB2 = 0;      //BWD low
    LATB1 = 1;      //FWD high
}

void vent_send_status(enum VALVE_STATE req_state) {
    // TODO
}
