#ifndef BOARD_H
#define BOARD_H

#include "message_types.h"

// Contains miscellaneous board-specific code

#define VENT_BOARD (BOARD_UNIQUE_ID & 0x8)

// If I am not a VENT, then I am an INJECTOR
#if VENT_BOARD
#define INJECTOR_BOARD 0
#else
#define INJECTOR_BOARD 1
#endif

#if INJECTOR_BOARD
#define SAFE_STATE ACTUATOR_OPEN
#define ACTUATOR_ID ACTUATOR_INJECTOR_VALVE
#define BATTERY_SENSOR_ID SENSOR_INJ_BATT
#elif VENT_BOARD
#define SAFE_STATE ACTUATOR_OPEN
#define ACTUATOR_ID ACTUATOR_VENT_VALVE
#define BATTERY_SENSOR_ID SENSOR_VENT_BATT
#endif

#define MAX_LOOP_TIME_DIFF_ms 250

#define RED_LED_ON()    (LATC4 = 0)
#define RED_LED_OFF()   (LATC4 = 1)
#define WHITE_LED_ON()  (LATC3 = 0)
#define WHITE_LED_OFF() (LATC3 = 1)
#define BLUE_LED_ON()   (LATC2 = 0)
#define BLUE_LED_OFF()  (LATC2 = 1)

#define RELAY_OFF()     (LATB5 = 0)
#define RELAY_ON()      (LATB5 = 1)


void LED_init(void);

#endif	/* BOARD_H */

