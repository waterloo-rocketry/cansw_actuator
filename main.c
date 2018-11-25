#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#define _XTAL_FREQ 1000000

#define RED_LED_ON (LATC5 = 0)
#define RED_LED_OFF (LATC5 = 1)
#define WHITE_LED_ON (LATC6 = 0)
#define WHITE_LED_OFF (LATC6 = 1)
#define BLUE_LED_ON (LATC7 = 0)
#define BLUE_LED_OFF (LATC7 = 1)

void led_init() {
    TRISC5 = 0;
    LATC5 = 1;      // turn the led off
    
    TRISC6 = 0;
    LATC6 = 1;      // turn the led off
    
    TRISC7 = 0;
    LATC7 = 1;      // turn the led off
}

int main(int argc, char** argv) {
    led_init();
    
    while (1){
        RED_LED_ON;
        WHITE_LED_ON;
        BLUE_LED_ON;
        __delay_ms(100);
        
        RED_LED_OFF;
        WHITE_LED_OFF;
        BLUE_LED_OFF;
        __delay_ms(100);
    }
    
    return (EXIT_SUCCESS);
}

