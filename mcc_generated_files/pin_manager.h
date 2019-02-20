/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F26K83
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set channel_VBAT aliases
#define channel_VBAT_TRIS                 TRISAbits.TRISA0
#define channel_VBAT_LAT                  LATAbits.LATA0
#define channel_VBAT_PORT                 PORTAbits.RA0
#define channel_VBAT_WPU                  WPUAbits.WPUA0
#define channel_VBAT_OD                   ODCONAbits.ODCA0
#define channel_VBAT_ANS                  ANSELAbits.ANSELA0
#define channel_VBAT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define channel_VBAT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define channel_VBAT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define channel_VBAT_GetValue()           PORTAbits.RA0
#define channel_VBAT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define channel_VBAT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define channel_VBAT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define channel_VBAT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define channel_VBAT_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define channel_VBAT_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define channel_VBAT_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define channel_VBAT_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set channel_VSENSE aliases
#define channel_VSENSE_TRIS                 TRISAbits.TRISA1
#define channel_VSENSE_LAT                  LATAbits.LATA1
#define channel_VSENSE_PORT                 PORTAbits.RA1
#define channel_VSENSE_WPU                  WPUAbits.WPUA1
#define channel_VSENSE_OD                   ODCONAbits.ODCA1
#define channel_VSENSE_ANS                  ANSELAbits.ANSELA1
#define channel_VSENSE_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define channel_VSENSE_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define channel_VSENSE_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define channel_VSENSE_GetValue()           PORTAbits.RA1
#define channel_VSENSE_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define channel_VSENSE_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define channel_VSENSE_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define channel_VSENSE_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define channel_VSENSE_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define channel_VSENSE_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define channel_VSENSE_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define channel_VSENSE_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()               do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()                do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()                do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()       do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()      do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSELA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set channel_LINAC_POT aliases
#define channel_LINAC_POT_TRIS                 TRISBbits.TRISB5
#define channel_LINAC_POT_LAT                  LATBbits.LATB5
#define channel_LINAC_POT_PORT                 PORTBbits.RB5
#define channel_LINAC_POT_WPU                  WPUBbits.WPUB5
#define channel_LINAC_POT_OD                   ODCONBbits.ODCB5
#define channel_LINAC_POT_ANS                  ANSELBbits.ANSELB5
#define channel_LINAC_POT_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define channel_LINAC_POT_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define channel_LINAC_POT_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define channel_LINAC_POT_GetValue()           PORTBbits.RB5
#define channel_LINAC_POT_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define channel_LINAC_POT_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define channel_LINAC_POT_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define channel_LINAC_POT_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define channel_LINAC_POT_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define channel_LINAC_POT_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define channel_LINAC_POT_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define channel_LINAC_POT_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()               do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()                do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()                do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()       do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()      do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()               do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()                do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()                do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()       do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()      do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/