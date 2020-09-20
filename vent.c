#include <xc.h>

void LED_init(void) {
    TRISD2 = 0;     //set C5 as output
    LATD2 = 1;      // turn the led off
    
    TRISD3 = 0;
    LATD3 = 1;      // turn the led off
    
    TRISD4 = 0;
    LATD4 = 1;      // turn the led off
}
