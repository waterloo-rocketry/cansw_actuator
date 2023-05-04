#ifndef BOARD_H
#define BOARD_H

#include "message_types.h"

// Contains miscellaneous board-specific code

// Change this to choose which board to use
#define INJECTOR_BOARD

#ifdef INJECTOR_BOARD
#define SAFE_STATE ACTUATOR_OFF
#define ACTUATOR_ID ACTUATOR_INJECTOR_VALVE
#endif

#ifdef VENT_BOARD
#define SAFE_STATE ACTUATOR_OFF
#define ACTUATOR_ID ACTUATOR_VENT_VALVE
#endif

#ifdef CAMERA
#define SAFE_STATE ACTUATOR_OFF
#define ACTUATOR_ID ACTUATOR_CAMERA_VALVE
#endif

#ifndef SAFE_STATE
#error "Invalid actuator board identifier"
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

