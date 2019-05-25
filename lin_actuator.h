#ifndef LINAC_H
#define	LINAC_H

#include <stdbool.h>
#include "canlib/message_types.h"

#define HIGH_DAC_ADDRESS 0x4d
#define LOW_DAC_ADDRESS 0x4c

#define LIN_ACT_UPPER_LIMIT_mV 2320
#define LIN_ACT_LOWER_LIMIT_mV 480
#define LIN_ACT_TOLERANCE_mV 50

#define HIGH_DAC_VAL 116                //from 0-255, multiply  desired voltage by 51
#define mV_TO_BIN_SCALING_FACTOR 0.051

bool lin_actuator_dac_init(void);
void lin_actuator_init(void);

void vent_open(void);
void vent_close(void);
void vent_send_status(enum VALVE_STATE req_state);


#endif	/* LINAC_H */

