#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/can_tx_buffer.h"

#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/mcc.h"
#include "lin_actuator.h"
#include "vent.h"
#include "timer.h"

bool lin_actuator_dac_init(void) {
  uint8_t data_buf[2];

  data_buf[0] = ((HIGH_DAC_VAL & 0xf0) >> 4);
  data_buf[1] = ((HIGH_DAC_VAL & 0x0f) << 4);
  i2c1_writeNBytes(HIGH_DAC_ADDRESS, data_buf, 2);

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
    // This is the same as the injector valve status. We don't report POT status
    enum VALVE_STATE curr_state;

    adc_result_t pot_raw = ADCC_GetSingleConversion(channel_LINAC_POT);
    // Vref: 4.096V, Resolution: 12 bits -> raw ADC value is precisely in mV
    uint16_t pot_voltage_mV = (uint16_t)pot_raw;

    // Potentiometer       --------v
    // LOWER_LIMIT (OPEN) |<--------------------------------->| UPPER_LIMIT (CLOSED)

    // close to the lower voltage limit (retracted)
    if (pot_voltage_mV - LIN_ACT_LOWER_LIMIT_mV < LIN_ACT_TOLERANCE_mV) {
        curr_state = VALVE_OPEN;

    // close to upper voltage limit (extended)
    } else if (LIN_ACT_UPPER_LIMIT_mV - pot_voltage_mV < LIN_ACT_TOLERANCE_mV) {
        curr_state = VALVE_CLOSED;

    // somewhere in between, but not close to either
    } else if (LIN_ACT_LOWER_LIMIT_mV < pot_voltage_mV
            && pot_voltage_mV < LIN_ACT_UPPER_LIMIT_mV) {
        curr_state = VALVE_UNK;

    // outside the voltage limits
    } else {
        curr_state = VALVE_ILLEGAL;
    }

    can_msg_t stat_msg;
    build_valve_stat_msg(millis(), curr_state, req_state, MSG_VENT_VALVE_STATUS, &stat_msg);
    txb_enqueue(&stat_msg);
}
