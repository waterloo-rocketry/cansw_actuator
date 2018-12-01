/**
  I2C1 Generated Driver API Header File
  
  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.h
	
  @Summary
    This is the generated header file for the I2C1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for I2C1.
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

#ifndef I2C1_H
#define I2C1_H

#include <stdint.h>
/**
 Section: Data Type Definitions
*/

/**
  I2C Driver Message Status Type Enumeration

  @Summary
    Defines the different message status when processing I2C request

  @Description
    This type enumeration specifies the different types of errors or status
    that an i2c request will have. For every submission of an i2c
    transaction, the status of that transaction is available.
    Based on the status, new transactions can be requested to the
    driver or a recovery can be performed to resend the transaction.

 */
typedef enum { I2C1_GOOD, I2C1_FAIL_TIMEOUT } i2c_error;
/**
  @Summary
    Initializes the I2C1

  @Description
    This routine initializes the I2C1.
    This routine must be called before any other i2c1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment

  
  @Example
    <code>
    I2C1_Initialize();
    </code>
*/
void I2C1_Initialize(void);

i2c_error i2c1_getLastError(void);
/**
  @Summary
    Read a byte of data from the I2C slave having 7 bit Address.

  @Description
    This routine reads a byte of data from a register of an I2C slave.

  @Preconditions
    None

  @Param
    address - The address of the i2c slave to be accessed

  @Param
    reg - The address of the register of the i2c slave to be read
 
  @Returns
    A data byte received by the driver.
*/
uint8_t i2c1_read1ByteRegister(uint8_t address, uint8_t reg);

/**
  @Summary
    Read a two byte wide register of the I2C slave having 7 bit Address.

  @Description
    This routine reads a two byte wide register of the I2C slave.

  @Preconditions
    None

  @Param
    address - The address of the i2c slave to be accessed

  @Param
    reg - The address of the two byte wide register of the i2c slave to be read
 
  @Returns
    Two bytes of data received from I2C slave register.
*/
uint16_t i2c1_read2ByteRegister(uint8_t address, uint8_t reg);

 /**
  @Summary
    Writes a byte of data to a register of an I2C slave having 7 bit Address.

  @Description
    This routine writes a byte of data to a register of an I2C slave which is byte wide.

  @Preconditions
  None

  @Param
    address - The address of the i2c slave to be accessed

  @Param
    reg - The address of the register of the i2c slave to be written
 
  @Param
    data  - Data byte to write to the register of an I2C slave 

  @Returns
    None
*/
void i2c1_write1ByteRegister(uint8_t address, uint8_t reg, uint8_t data);

 /**
  @Summary
    Writes two bytes of data to a register of an I2C slave having 7 bit Address.

  @Description
    This routine writes two bytes of data to a register of an I2C slave.

  @Preconditions
  None

  @Param
    address - The address of the i2c slave to be accessed

  @Param
    reg - The address of the register of the i2c slave to be written
 
  @Param
    data  - Data word to write to the register of an I2C slave 

  @Returns
    None
*/
void i2c1_write2ByteRegister(uint8_t address, uint8_t reg, uint16_t data);

 /**
  @Summary
    Writes n bytes of data to an I2C slave having 7 bit Address.

  @Description
    This routine writes n bytes of data to an I2C slave.

  @Preconditions
  None

  @Param
    address - The address of the i2c slave to be accessed
 
  @Param
    *data - A pointer to the memory location where data to be written to I2C slave is stored  

  @Param
    len - The length of the data block to be written
  
  @Returns
    None
*/
void i2c1_writeNBytes(uint8_t address, void * data, uint8_t len);


void i2c1_write2Bytes(uint8_t address, uint8_t byte1, uint8_t byte2);

 /**
  @Summary
    Read n bytes of data block from a register/address of an I2C slave having 7 bit Address.

  @Description
    This routine reads n bytes of data from a register/address of an I2C slave.

  @Preconditions
  None

  @Param
    address - The address of the i2c slave to be accessed
 
  @Param
    *data - A pointer to the memory location where received data will be stored 

  @Param
    len - The length of the data block to be read
  
  @Returns
    None
*/
void i2c1_readDataBlock(uint8_t address, uint8_t reg, char *data, uint8_t len);

#endif	/* I2C1_H */

