#ifndef ERROR_CHECKS_H
#define	ERROR_CHECKS_H

#include "canlib/message_types.h"

#include <stdbool.h>

// at this voltage, the vent valve will automatically open if closed
#define VENT_BATT_UNDERVOLTAGE_PANIC_THRESHOLD_mV 7500

// at this voltage, a warning will be sent out over CAN
#define VENT_BATT_UNDERVOLTAGE_THRESHOLD_mV 8000

// at this voltage, a warning will be sent out over CAN
#define VENT_BATT_OVERVOLTAGE_THRESHOLD_mV 9500

// From bus line. At this current, a warning will be sent out over CAN
#define VENT_OVERCURRENT_THRESHOLD_mA 300

// If we don't hear CAN traffic for this long, the vent valve will automatically open
#define MAX_CAN_IDLE_TIME_MS 1000

// General board status checkers
bool check_battery_voltage_error(void);
bool is_batt_voltage_critical(void);
bool check_bus_current_error(void);
bool check_valve_pin_error(enum VALVE_STATE req_state);
bool check_valve_pot_error(void);

#endif	/* ERROR_CHECKS_H */

