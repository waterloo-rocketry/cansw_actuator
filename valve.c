#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/can_tx_buffer.h"

#include "mcc_generated_files/mcc.h"

#include "valve.h"
#include "vent.h"
#include "timer.h"

void valve_init(void){
    TRISB5 = 0; // set VALVE_CONTROL (pin 26) as output
    LATB5 = 0; // this opens the valve, which is what we want on startup

    TRISB4 = 1; // set LIMIT_OPEN (pin 25) as input
    ANSELB4 = 0; // set as digital input

    TRISB3 = 1; // set LIMIT_CLOSED (pin 24) as input
    ANSELB3 = 0; // set as digital input
}

void vent_open(void){
    WHITE_LED_ON();
    LATB5 = 0;
}

void vent_close(void){
    WHITE_LED_OFF();
    LATB5 = 1;
}

bool get_valve_open_state(void){
    return PORTBbits.RB4;
}

bool get_valve_closed_state(void){
    return PORTBbits.RB3;
}

void vent_send_status(enum VALVE_STATE req_state) {
    // This is the same as the injector valve status.
    enum VALVE_STATE curr_state;

    bool valve_open = get_valve_open_state();
    bool valve_closed = get_valve_closed_state();

    // open
    if (valve_open && !valve_closed){
        curr_state = VALVE_OPEN;
    }

    // closed
    else if (!valve_open && valve_closed){
        curr_state = VALVE_CLOSED;
    }

    // in between open and closed
    else if (!valve_open && !valve_closed){
        curr_state = VALVE_UNK;
    }

    // both limit switches triggered ie. both open and closed (illegal)
    else {
        curr_state = VALVE_ILLEGAL;
    }

    can_msg_t stat_msg;
    build_valve_stat_msg(millis(), curr_state, req_state,
            MSG_VENT_VALVE_STATUS, &stat_msg);
    txb_enqueue(&stat_msg);
}
