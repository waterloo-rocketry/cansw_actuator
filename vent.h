#ifndef VENT_H
#define	VENT_H

// Contains miscellaneous vent board-specific code

#define MAX_LOOP_TIME_DIFF_ms 250

#define RED_LED_ON() (LATC4 = 0)
#define RED_LED_OFF() (LATC4 = 1)
#define WHITE_LED_ON() (LATC3 = 0)
#define WHITE_LED_OFF() (LATC3 = 1)
#define BLUE_LED_ON() (LATC2 = 0)
#define BLUE_LED_OFF() (LATC2 = 1)

void LED_init(void);

#endif	/* VENT_H */

