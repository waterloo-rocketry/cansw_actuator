#ifndef ERROR_CHECKS_H
#define	ERROR_CHECKS_H

#include "canlib/message_types.h"

#include <stdbool.h>

// FIXME: these values need to be nailed down
#define VENT_BATT_UNDERVOLTAGE_THRESHOLD_mV 8500        // on valve batt
#define VENT_BATT_OVERVOLTAGE_THRESHOLD_mV 9500         // on valve batt
#define VENT_OVERCURRENT_THRESHOLD_mA 300               // from bus line
#define MAX_CAN_IDLE_TIME_MS 1000

// General board status checkers
bool check_battery_voltage_error(void);
bool check_bus_current_error(void);
bool check_valve_pin_error(enum VALVE_STATE req_state);
bool check_valve_pot_error(void);

#endif	/* ERROR_CHECKS_H */

