#include "valve.h"

void vent_init(void){
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

// TODO: do I really need to use snake_case in C? can I just refactor this entire codebase into camelCase?
bool getLimitOpenState(){
    return PORTBbits.RB4;
}

bool getLimitClosedState(){
    return PORTBbits.RB3;
}

void vent_send_status(enum VALVE_STATE req_state) {
    // This is the same as the injector valve status.
    enum VALVE_STATE curr_state;

    adc_result_t pot_raw = ADCC_GetSingleConversion(channel_LINAC_POT);
    // Vref: 4.096V, Resolution: 12 bits -> raw ADC value is precisely in mV
    uint16_t pot_voltage_mV = (uint16_t)pot_raw;

    bool limit_open = getLimitOpenState();
    bool limit_closed = getLimitClosedState();

    // open
    if (limit_open && !limit_closed){
        curr_state = VALVE_OPEN;
    }

    // closed
    else if (!limit_open && limit_closed){
        curr_state = VALVE_CLOSED;
    }

    // in between open and closed
    else if (!limit_open && !limit_closed){
        curr_state = VALVE_UNK;
    }

    // both limit switches triggered ie. both open and closed (illegal)
    } else {
        curr_state = VALVE_ILLEGAL;
    }

    can_msg_t stat_msg;
    build_valve_stat_msg(millis(), curr_state, req_state, MSG_VENT_VALVE_STATUS, &stat_msg);
    txb_enqueue(&stat_msg);
}
