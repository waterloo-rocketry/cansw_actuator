#ifndef VENT_H
#define	VENT_H

// Contains miscellaneous vent board-specific code

#define MAX_LOOP_TIME_DIFF_ms 250

#define RED_LED_ON() (LATD2 = 0)
#define RED_LED_OFF() (LATD2 = 1)
#define WHITE_LED_ON() (LATD3 = 0)
#define WHITE_LED_OFF() (LATD3 = 1)
#define BLUE_LED_ON() (LATD4 = 0)
#define BLUE_LED_OFF() (LATD4 = 1)

void LED_init(void);

#endif	/* VENT_H */

