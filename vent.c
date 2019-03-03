#include <stdlib.h>
#include <xc.h>

#include "mcc_generated_files/adcc.h"

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/message_types.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"

#include "timer.h"
#include "vent.h"

void LED_init(void) {
    TRISC5 = 0;     //set C5 as output
    LATC5 = 1;      // turn the led off
    
    TRISC6 = 0;
    LATC6 = 1;      // turn the led off
    
    TRISC7 = 0;
    LATC7 = 1;      // turn the led off
}





//******************************************************************************
//                              STATUS CHECKS                                 //
//******************************************************************************

// FIXME
int check_battery_voltage(void){    //returns mV
    return (int)(ADCC_GetSingleConversion(channel_VBAT)*3.95); // scaled by value calculated via testing
}

// FIXME
int check_current_draw(void){       //returns mA
    return (int)(ADCC_GetSingleConversion(channel_VSENSE)/20); //i =v/r r = 0.2 ohms, v = VSENCE/100
}


// Send a CAN message with nominal status
void send_status_ok(void) {
    can_msg_t board_stat_msg;
    board_stat_msg.sid = MSG_GENERAL_BOARD_STATUS | BOARD_UNIQUE_ID;

    // capture the most recent timestamp
    uint32_t last_millis = millis();

    // paste in the timestamp one byte at a time. Most significant byte goes in data[0].
    board_stat_msg.data[0] = (last_millis >> 16) & 0xff;
    board_stat_msg.data[1] = (last_millis >> 8) & 0xff;
    board_stat_msg.data[2] = (last_millis >> 0) & 0xff;

    // set the error code
    board_stat_msg.data[3] = E_NOMINAL;

    // 3 byte timestamp + 1 byte error code
    board_stat_msg.data_len = 4;

    // send it off at low priority
    can_send(&board_stat_msg, 0);
}


