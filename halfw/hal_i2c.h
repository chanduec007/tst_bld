/***********************************************************
 * PROJECT NAME: HMI Application Framework

 * Platform: BBB

 * @file: hal_i2c.h

 * Function: I2C Interface module header APIs

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***********************************************************/
#ifndef I2C_MODULE_H
#define I2C_MODULE_H

#define I2C0_path       "/dev/i2c-0"              
#define I2C1_path       "/dev/i2c-1"    

typedef enum {
	      i2c0=0, 
	      i2c1}i2c_t;

int i2c_init(i2c_t i2c_bus);
unsigned char i2c_read(unsigned char deviceAddress, unsigned char reg, int i2c1_fd);
int i2c_write(unsigned char deviceAddress, unsigned char reg, unsigned char val, int i2c1_fd);
signed short i2c_read_short(unsigned char deviceAddress, unsigned char reg, int i2c1_fd);

#endif
