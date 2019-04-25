#include <xc.h>

void LED_init(void) {
    TRISC5 = 0;     //set C5 as output
    LATC5 = 1;      // turn the led off
    
    TRISC6 = 0;
    LATC6 = 1;      // turn the led off
    
    TRISC7 = 0;
    LATC7 = 1;      // turn the led off
}
