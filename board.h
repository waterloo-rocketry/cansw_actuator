#ifndef BOARD_H
#define BOARD_H

#include "message_types.h"

// Contains miscellaneous board-specific code

// Change this to choose which board to use
#define CAMERA1

#ifdef INJECTOR
#define SAFE_STATE ACTUATOR_OFF
// We want the injector valve safe state to be "stay where you are"
// so just disable the logic that goes to safe state
#define SAFE_STATE_ENABLED 0
#define ACTUATOR_ID ACTUATOR_INJECTOR_VALVE
#define HALL_THRESHOLD 2000
#define HALL_ERR_THRESHOLD 4090
#define HIGH_STATE ACTUATOR_ON
#define HAS_LIMS 1
#define MAX_CAN_IDLE_TIME_MS 10000
#endif

#ifdef VENT
#define SAFE_STATE ACTUATOR_OFF
#define SAFE_STATE_ENABLED 1
#define ACTUATOR_ID ACTUATOR_VENT_VALVE
#define HAS_LIMS 0
#define MAX_CAN_IDLE_TIME_MS 10000
#endif

#ifdef CAMERA1
#define SAFE_STATE ACTUATOR_OFF
#define SAFE_STATE_ENABLED 1
#define ACTUATOR_ID ACTUATOR_CAMERAS
#define HAS_LIMS 0
#define MAX_CAN_IDLE_TIME_MS 900000
#endif

#ifdef CAMERA2
#define SAFE_STATE ACTUATOR_OFF
#define SAFE_STATE_ENABLED 1
#define ACTUATOR_ID ACTUATOR_CAMERAS
#define HAS_LIMS 0
#define MAX_CAN_IDLE_TIME_MS 900000
#endif

#ifndef SAFE_STATE
#error "Invalid actuator board identifier"
#endif

#define MAX_LOOP_TIME_DIFF_ms 250
#define MAX_BUS_DEAD_TIME_ms 1000

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

