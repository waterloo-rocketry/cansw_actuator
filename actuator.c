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

#define HAS_LIMS 1

void actuator_init(){
    TRISB5 = 0; // set ACTUATOR_CONTROL (pin 26) as output
    if (SAFE_STATE == ACTUATOR_OPEN) {
        RELAY_OFF();
    } else if (SAFE_STATE == ACTUATOR_CLOSED) {
        RELAY_ON();
    } else {
        // Should not get here.
        while (1) {}; // panic, this will be caught early on in testing
    }
    
    TRISB4 = 1; // set LIMIT_OPEN (pin 25) as input
    ANSELB4 = 0; // set as digital input

    TRISB3 = 1; // set LIMIT_CLOSED (pin 24) as input
    ANSELB3 = 0; // set as digital input
}

void actuator_set(enum ACTUATOR_STATE state) {
    if (state == ACTUATOR_OPEN) {
        WHITE_LED_OFF();
        RELAY_OFF();
    } else if (state == ACTUATOR_CLOSED) {
        WHITE_LED_ON();
        RELAY_ON();
    }
}

enum ACTUATOR_STATE get_actuator_state(void) {
#if !HAS_LIMS
    return ACTUATOR_UNK;
#else
    // read limit switch values
    bool actuator_open = PORTBbits.RB4;
    bool actuator_closed = PORTBbits.RB3;
    
    if (actuator_open && !actuator_closed) { return ACTUATOR_OPEN; }
    if (!actuator_open && actuator_closed) { return ACTUATOR_CLOSED; }
    if (!actuator_open && !actuator_closed) { return ACTUATOR_UNK; }
    return ACTUATOR_ILLEGAL; // both limit switches at same time
#endif
}

void actuator_send_status(enum ACTUATOR_STATE req_state) {
    enum ACTUATOR_STATE curr_state = get_actuator_state();

    can_msg_t stat_msg;
    build_actuator_stat_msg(millis(), ACTUATOR_ID, curr_state, req_state, &stat_msg);
    txb_enqueue(&stat_msg);
}
