#include <xc.h>
#include "LINAC.h"

 void LINAC_init() {
    TRISB1 = 0;     //set MOTOR_FWD as output
    LATB1 = 0;
    
    TRISB2 = 0;     //set MOTOR_BWD as output
    LATB2 = 0;
    
    TRISB3 = 1;     //set LIM_HIGH as input
    ANSELB3 = 0;    //set as digital input
    
    TRISB4 = 1;     //set LIM_LOW as input
    ANSELB4 = 0;    //set as digital input
    
}
 
int open_vent(){
    LATB1 = 1;      //FWD High
    LATB2 = 0;      //BWD Low
    while(RB3)
    {}
    return 1;
    
}
int close_vent(){
    LATB2 = 1;      //BWD High
    LATB1 = 0;      //FWD Low
    while(RB4)
    {}
    return 1;
}