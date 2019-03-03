#ifndef VENT_H
#define	VENT_H

// Contains miscellaneous vent board-specific code

#define RED_LED_ON() (LATC5 = 0)
#define RED_LED_OFF() (LATC5 = 1)
#define WHITE_LED_ON() (LATC6 = 0)
#define WHITE_LED_OFF() (LATC6 = 1)
#define BLUE_LED_ON() (LATC7 = 0)
#define BLUE_LED_OFF() (LATC7 = 1)

void LED_init(void);

// FIXME
int check_battery_voltage(void);
int check_current_draw(void);
void send_status_ok(void);


#endif	/* VENT_H */

