#include <xc.h>
#include "lin_actuator.h"

 void lin_actuator_init() {
    TRISB1 = 0;     //set MOTOR_FWD as output
    LATB1 = 0;
    
    TRISB2 = 0;     //set MOTOR_BWD as output
    LATB2 = 0;
    
    TRISB3 = 1;     //set LIM_HIGH as input
    ANSELB3 = 0;    //set as digital input
    
    TRISB4 = 1;     //set LIM_LOW as input
    ANSELB4 = 0;    //set as digital input
    
    ANSELB5 = 1;
    TRISB5 = 1;
    
}
 
void open_vent(void){
    LATB1 = 0;      //FWD low
    LATB2 = 1;      //BWD high  
    moving = opening;
}
void close_vent(void){
    LATB2 = 0;      //BWD low
    LATB1 = 1;      //FWD high
    moving = closing;
}

lin_actuator_states check_vent_status(void){
    lin_actuator_states status = nominal;
    
    if(moving == opening){
        if(!RB4){
            LATB1 = 0;
            LATB2 = 0;
            moving = stopped;
        }
        else{
            status = opening;
        }
        
    }
    else if(moving == closing){
        if(!RB3){
            LATB1 = 0;
            LATB2 = 0;
            moving = stopped;
        }
        else{
            status = closing;
        }
    }
    else{
        if(RB3 && RB4){
          status = stopped_between_states; 
        }
    }
    if(!RB4){
            status = open;
    }
    if(!RB3){
            status = closed;
    }
    return status;
}