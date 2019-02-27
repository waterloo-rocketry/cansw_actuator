/* 
 * File:   LINAC.h
 * Author: zx100
 *
 * Created on February 10, 2019, 12:25 AM
 */

#ifndef LINAC_H
#define	LINAC_H

typedef enum
{
    nominal =  0,
    open = 1,
    closed = 2,
    opening = 3,
    closing = 4,
    stopped_between_states =  5,
    in_motion =  6,
    stopped = 7
} lin_actuator_states;


lin_actuator_states moving = stopped;

void lin_actuator_init(void);

void open_vent(void);

void close_vent(void);

lin_actuator_states check_vent_status(void);


#endif	/* LINAC_H */

