/**
  I2C1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.c

  @Summary
    This is the generated header file for the I2C1 driver using 
    PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for I2C1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F26K83
        Driver Version    :  2.02
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

/*
 This file provides some basic blocking helper functions for common operations on the i2c API
 */
#include <xc.h>
#include <stdbool.h>
#include "i2c1.h"
#include "mcc.h"
static i2c_error lastError = I2C1_GOOD;

void I2C1_Initialize(void)
{
	if(!I2C1CON0bits.EN || lastError != I2C1_GOOD)
    {
		lastError = I2C1_GOOD;
		// TXU 0; CSD Clock Stretching enabled; ACKT 0; RXO 0; ACKDT Acknowledge; ACKSTAT ACK received; ACKCNT Acknowledge; 
		I2C1CON1 = 0x00;
		// ABD enabled; GCEN disabled; ACNT disabled; SDAHT 100 ns hold time; BFRET 8 I2C Clock pulses; FME enabled; 
		I2C1CON2 = 0x24;
		// CLK Fosc/4; 
		I2C1CLK = 0x00;
		// CSTR Enable clocking; S Cleared by hardware after Start; MODE 7-bit address; EN enabled; RSEN disabled; 
		I2C1CON0 = 0x84;
		I2C1PIR = 0;//    ;Clear all the error flags
		I2C1ERR = 0;
	}
}

i2c_error i2c1_getLastError(void)
{
    return lastError;
}

static inline void sendByte(uint8_t data)
{
    uint8_t delayCounter = 255;
    if(lastError == I2C1_GOOD)
    {
        while(--delayCounter)
        {
            if(I2C1STAT1bits.TXBE)
            {
                I2C1TXB = data;
                return;
            }
            else
            {
                __delay_us(1);
            }
        }
        lastError = I2C1_FAIL_TIMEOUT;
    }
}

static inline uint8_t receiveByte(void)
{
    uint8_t delayCounter = 255;
    if(lastError == I2C1_GOOD)
    {
        while(--delayCounter)
        {
            if(I2C1STAT1bits.RXBF)
            {
                return I2C1RXB;
            }
            else
            {
                __delay_us(1);
            }
        }
        lastError = I2C1_FAIL_TIMEOUT;
    }
	return 0;
}

static inline void wait4Stop(void)
{
    uint8_t waitCount=255;
    if(lastError == I2C1_GOOD)
    {
        while(--waitCount)
        {
            if(I2C1PIRbits.PCIF)
            {
                return;
            }
            else
            {
                __delay_us(1);
            }
        }
        lastError = I2C1_FAIL_TIMEOUT;
    }
}

static inline void wait4Ack(void)
{
    uint8_t waitCount=255;
    if(lastError == I2C1_GOOD)
    {
        while(--waitCount)
        {
            if(!I2C1CON1bits.ACKSTAT)
            {
                return;
            }
            else
            {
                __delay_us(1);
            }
        }
        lastError = I2C1_FAIL_TIMEOUT;
    }
}

static inline void wait4MDRSetcount(uint8_t count)
{
    uint8_t waitCount=255;
    if(lastError == I2C1_GOOD)
    {
        while(--waitCount)
        {
            if(I2C1CON0bits.MDR)
            {
                I2C1CNT = count;
                return;
            }
            else
            {
                __delay_us(1);
            }
        }
        lastError = I2C1_FAIL_TIMEOUT;
    }
}

void i2c1_write1ByteRegister(uint8_t address, uint8_t reg, uint8_t data)
{
    I2C1_Initialize();
    I2C1ADB1= (uint8_t)(address<<1);
    I2C1CNT=2;
    I2C1CON0bits.S=1;
    sendByte(reg);
    sendByte(data);
    wait4Stop();
}

void i2c1_writeNBytes(uint8_t address, void* data, uint8_t len)
{
    uint8_t *dataPointer = data;

    I2C1_Initialize();
    I2C1ADB1= (uint8_t)(address<<1);
    I2C1CNT=len;
    I2C1CON0bits.S=1; //Start
    while(len--)
    {
        sendByte(*dataPointer++);
    }
    wait4Stop();
}
void i2c1_write2Bytes(uint8_t address, uint8_t byte1, uint8_t byte2)
{
    I2C1_Initialize();
    I2C1ADB1= (uint8_t)(address<<1);
    I2C1CNT=2;
    I2C1CON0bits.S=1; //Start
    sendByte(byte1);
    sendByte(byte2);
    wait4Stop();
}
uint8_t i2c1_read1ByteRegister(uint8_t address, uint8_t reg)
{
    uint8_t result;

    I2C1_Initialize();
    I2C1ADB1= (uint8_t)(address<<1);
    I2C1CNT=1;
    I2C1CON0bits.RSEN=1;
    I2C1CON0bits.S=1; //Start
    while (I2C1CON0bits.S);
    sendByte(reg);
    wait4MDRSetcount(1);
    address = (uint8_t)(address<<1);
    I2C1ADB1= (uint8_t)(address| 0x01); //Change the R/W bit for read
    I2C1CON0bits.S=1; //Start
    I2C1CON0bits.RSEN=0;
    result = receiveByte();
    wait4Stop();
    return result;
}


uint16_t i2c1_read2ByteRegister(uint8_t address, uint8_t reg)
{
    uint16_t    result;

    I2C1_Initialize();
    I2C1ADB1= (uint8_t)(address<<1);
    I2C1CNT=1;
    I2C1CON0bits.RSEN=1;
    I2C1CON0bits.S=1; //Start
    while (I2C1CON0bits.S);
    sendByte(reg);
    wait4Ack();
    wait4MDRSetcount(2);
    address=(uint8_t)(address<<1);
    I2C1ADB1= (uint8_t)(address| 0x01); //Change the R/W bit for read
    I2C1CON0bits.S=1; //Start
    while(I2C1CON0bits.S);
    I2C1CON0bits.RSEN=0;
    result = receiveByte();//read MSB of the 2byte register
    result = result<<8;
    result = result | receiveByte();//read LSB of the 2byte register
    wait4Stop();
    return result;
}

void i2c1_write2ByteRegister(uint8_t address, uint8_t reg, uint16_t data)
{
    I2C1_Initialize();
    I2C1ADB1= (uint8_t)(address<<1);
    I2C1CNT=3;
    I2C1CON0bits.S=1; //Start
    sendByte(reg);
    sendByte(data>>8);
    sendByte(data & 0x00FF);
    wait4Stop();
}

void i2c1_readDataBlock(uint8_t address, uint8_t reg, char *data, uint8_t len)
{
    I2C1_Initialize();
    I2C1ADB1= (uint8_t)(address<<1);
    I2C1CNT=1;
    I2C1CON0bits.RSEN=1;
    I2C1CON0bits.S=1; //Start
    sendByte(reg);
    wait4Ack();
    wait4MDRSetcount(len);
    address=(uint8_t)(address<<1);
    I2C1ADB1= (uint8_t)(address| 0x01); //Change the R/W bit for read
    I2C1CON0bits.S=1; //Start
    I2C1CON0bits.RSEN=0;
    while(len--)
    {
        *data++ = receiveByte();
    }
    wait4Stop();
}

