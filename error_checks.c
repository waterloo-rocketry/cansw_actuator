#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"

#include "mcc_generated_files/fvr.h"
#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/mcc.h"

#include "timer.h"
#include "vent.h"
#include "error_checks.h"

#include <stdlib.h>

//******************************************************************************
//                              STATUS CHECKS                                 //
//******************************************************************************

bool check_battery_voltage_error(void){    //returns mV
    adc_result_t batt_raw = ADCC_GetSingleConversion(channel_VBAT);

    // Vref: 4.096V, Resolution: 12 bits -> raw ADC value is precisely in mV
    uint16_t batt_voltage_mV = (uint16_t)batt_raw;

    // get the un-scaled battery voltage (voltage divider)
    // we don't care too much about precision - some truncation is fine
    batt_voltage_mV = batt_voltage_mV * 3.95; // scaled by value calculated via testing

    if (batt_voltage_mV < VENT_BATT_UNDERVOLTAGE_THRESHOLD_mV
            || batt_voltage_mV > VENT_BATT_OVERVOLTAGE_THRESHOLD_mV) {

        uint32_t timestamp = millis();
        uint8_t batt_data[2] = {0};
        batt_data[0] = (batt_voltage_mV >> 8) & 0xff;
        batt_data[1] = (batt_voltage_mV >> 0) & 0xff;
        enum BOARD_STATUS error_code = batt_voltage_mV < VENT_BATT_UNDERVOLTAGE_THRESHOLD_mV
                ? E_BATT_UNDER_VOLTAGE
                : E_BATT_OVER_VOLTAGE;

        can_msg_t error_msg;
        build_board_stat_msg(timestamp, error_code, batt_data, 2, &error_msg);
        can_send(&error_msg, 3);    // send at high priority
        return false;
    }

    // things look ok
    return true;
}

bool check_bus_current_error(void){
    adc_result_t sense_raw_mV = ADCC_GetSingleConversion(channel_VSENSE);
    int curr_draw_mA = (sense_raw_mV) / 20;

    if (curr_draw_mA > VENT_OVERCURRENT_THRESHOLD_mA) {
        uint32_t timestamp = millis();
        uint8_t curr_data[2] = {0};
        curr_data[0] = (curr_draw_mA >> 8) & 0xff;
        curr_data[1] = (curr_draw_mA >> 0) & 0xff;

        can_msg_t error_msg;
        build_board_stat_msg(timestamp, E_BUS_OVER_CURRENT, curr_data, 2, &error_msg);
        can_send(&error_msg, 3);    // send at high priority
        return false;
    }

    // things look ok
    return true;
}

bool check_valve_pin_error(enum VALVE_STATE req_state) {
    return true;
    
    // Error cases:
    // check that digital pin reads match what they should be (a la injector)
}

bool check_valve_pot_error(void) {
    return true;
    
    // Error case:
    // feedback potentiometer reading outside the range set by the DACs
}

