#ifndef LINAC_H
#define	LINAC_H

#define HIGH_DAC_ADDRESS 0x4d
#define LOW_DAC_ADDRESS 0x4c
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

void open_vent(void);
void close_vent(void);

lin_actuator_states check_vent_status(void);

#endif	/* LINAC_H */

