#ifndef LINAC_H
#define	LINAC_H

#include <stdbool.h>
#include "canlib/message_types.h"

#define HIGH_DAC_ADDRESS 0x4d
#define LOW_DAC_ADDRESS 0x4c

// TODO: use these instead of HIGH/LOW DAC VAL
#define LIN_ACT_UPPPER_LIMIT_mV 1000
#define LIN_ACT_LOWER_LIMIT_mV 98

#define mV_TO_BIN_SCALING_FACTOR 0.051

#define HIGH_DAC_VAL 51 //from 0-255, multiply  desired voltage by 51
#define LOW_DAC_VAL 5

typedef enum
{
    nominal,
    open,
    closed,
    opening,
    closing,
    stopped_between_states,
    in_motion,
    stopped
} lin_actuator_states;

bool lin_actuator_dac_init(void);
void lin_actuator_init(void);

void vent_open(void);
void vent_close(void);
void vent_send_status(enum VALVE_STATE req_state);


#endif	/* LINAC_H */

