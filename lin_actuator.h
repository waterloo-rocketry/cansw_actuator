/* 
 * File:   LINAC.h
 * Author: Zachariah Mears
 *
 * Created on February 10, 2019, 12:25 AM
 */

#ifndef LINAC_H
#define	LINAC_H

#define RED_LED_ON (LATC5 = 0)
#define RED_LED_OFF (LATC5 = 1)
#define WHITE_LED_ON (LATC6 = 0)
#define WHITE_LED_OFF (LATC6 = 1)
#define BLUE_LED_ON (LATC7 = 0)
#define BLUE_LED_OFF (LATC7 = 1)
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

void set_DACs();

void lin_actuator_init(void);

void open_vent(void);

void close_vent(void);

lin_actuator_states check_vent_status(void);


#endif	/* LINAC_H */

