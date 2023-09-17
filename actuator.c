#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/can_tx_buffer.h"

#include "mcc_generated_files/mcc.h"

#include "actuator.h"
#include "board.h"
#include "timer.h"

void actuator_init(){
    TRISB5 = 0; // set ACTUATOR_CONTROL (pin 26) as output
    if (SAFE_STATE == ACTUATOR_OFF) {
        RELAY_OFF();
    } else if (SAFE_STATE == ACTUATOR_ON) {
        RELAY_ON();
    } else {
        // Should not get here.
        while (1) {}; // panic, this will be caught early on in testing
    }
    
#ifdef INJECTOR
    LATB4 = 1;
    TRISB4 = 0; // set LIMIT_OPEN as output to power hall sensor

    TRISB3 = 1; // set LIMIT_CLOSED (pin 24) as input
    ANSELB3 = 1; // set as analog input
#else
    TRISB4 = 1; // set LIMIT_OPEN (pin 25) as input
    ANSELB4 = 0; // set as digital input

    TRISB3 = 1; // set LIMIT_CLOSED (pin 24) as input
    ANSELB3 = 0; // set as digital input
#endif
}

void actuator_set(enum ACTUATOR_STATE state) {
    if (state == ACTUATOR_OFF) {
        WHITE_LED_OFF();
        RELAY_OFF();
    } else if (state == ACTUATOR_ON) {
        WHITE_LED_ON();
        RELAY_ON();
    }
}

enum ACTUATOR_STATE get_actuator_state(void) {
#if !HAS_LIMS
    return ACTUATOR_UNK;
#else
// define in board.h
#ifdef INJECTOR
    adc_result_t hall_raw = ADCC_GetSingleConversion(channel_HALL);
    
    if (hall_raw > HALL_ERR_THRESHOLD) { return ACTUATOR_ILLEGAL; }
    // HIGH_STATE is defined in board.h as the ACTUATOR_STATE that a high
    // hall sensor reading maps to.
    if (hall_raw > HALL_THRESHOLD) { return HIGH_STATE; }
    return 1 - HIGH_STATE; // First two ACTUATOR_STATEs are on and off so this works to invert
#else
    // read limit switch values
    bool actuator_open = PORTBbits.RB4;
    bool actuator_closed = PORTBbits.RB3;
    
    if (actuator_open && !actuator_closed) { return ACTUATOR_OFF; }
    if (!actuator_open && actuator_closed) { return ACTUATOR_ON; }
    if (!actuator_open && !actuator_closed) { return ACTUATOR_UNK; }
    return ACTUATOR_ILLEGAL; // both limit switches at same time
#endif
#endif
}

void actuator_send_status(enum ACTUATOR_STATE req_state) {
// define in board.h
#ifdef INJECTOR
    adc_result_t hall_raw = ADCC_GetSingleConversion(channel_HALL);
    
    // Send a CAN message with the raw hall value
    can_msg_t hall_msg;
    build_analog_data_msg(millis(), SENSOR_MAG_1, hall_raw, &hall_msg);
    txb_enqueue(&hall_msg);
#endif
    enum ACTUATOR_STATE curr_state = get_actuator_state();

    can_msg_t stat_msg;
    build_actuator_stat_msg(millis(), ACTUATOR_ID, curr_state, req_state, &stat_msg);
    txb_enqueue(&stat_msg);
}
