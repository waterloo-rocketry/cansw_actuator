#ifndef VENT_H
#define	VENT_H

#include <stdbool.h>

// Contains miscellaneous vent board-specific code

#define RED_LED_ON() (LATC5 = 0)
#define RED_LED_OFF() (LATC5 = 1)
#define WHITE_LED_ON() (LATC6 = 0)
#define WHITE_LED_OFF() (LATC6 = 1)
#define BLUE_LED_ON() (LATC7 = 0)
#define BLUE_LED_OFF() (LATC7 = 1)

// FIXME: these values need to be nailed down
#define VENT_BATT_UNDERVOLTAGE_THRESHOLD_mV 8500        // on valve batt
#define VENT_BATT_OVERVOLTAGE_THRESHOLD_mV 9500         // on valve batt
#define VENT_OVERCURRENT_THRESHOLD_mA 300               // from bus line

void LED_init(void);

// General board status checkers
bool check_battery_voltage(void);
bool check_bus_voltage(void);
bool check_bus_current(void);
bool check_valve_status(void);

void send_status_ok(void);

#endif	/* VENT_H */

