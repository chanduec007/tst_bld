/***********************************************************
 * PROJECT NAME: HMI Application Framework

 * Platform: BBB

 * @file: hal_i2c.c

 * Function: I2C Interface module 

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***********************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <unistd.h>
#include <errno.h>
#include "hal_i2c.h"

/*============================================================================
* Function      : i2c_init
* IN            : None
* OUT           : None
* RETURN        : 
* INFO          : initialize the I2C. 
============================================================================*/
int i2c_init(i2c_t i2c_bus)
{
	int i2c1_fd;
	
	if(i2c_bus == i2c0)
	{	
		i2c1_fd = open(I2C0_path, O_RDWR);
	}
	else if(i2c_bus == i2c1)
	{
		i2c1_fd = open(I2C1_path, O_RDWR);
	}
	return i2c1_fd;	
}

/*============================================================================
* Function      : i2c_read
* IN            : None
* OUT           : None
* RETURN        : 
* INFO          : read the I2C. 
*============================================================================*/
unsigned char i2c_read(unsigned char deviceAddress, unsigned char reg, int i2c1_fd)
{
	if(ioctl(i2c1_fd, I2C_SLAVE, deviceAddress) < 0)
	{
		printf("Eroror while I2C address 0x%x: %d error\n:", deviceAddress, errno);
		return -1;	
	}
	
	union i2c_smbus_data data;
	struct i2c_smbus_ioctl_data args;
	int ret;

	args.read_write = I2C_SMBUS_READ;
	args.command = reg;
	args.size = I2C_SMBUS_BYTE_DATA;
	args.data = &data;
	ret = ioctl(i2c1_fd, I2C_SMBUS, &args);
	if (ret!=0) 
	{
        	perror("ioctl[fail]");
        	return 0xff;
        }
	return data.byte;
}

/*============================================================================
* Function      : i2c_write
* IN            : None
* OUT           : None
* RETURN        : 
* INFO          : write the I2C. 
*============================================================================*/
int i2c_write(unsigned char deviceAddress, unsigned char reg, unsigned char val, int i2c1_fd)                    
{
	if(ioctl(i2c1_fd, I2C_SLAVE, deviceAddress) < 0)                           
        {                                                                          
                printf("Eroror while I2C address 0x%x: %d error\n:", deviceAddress, errno);
                return -1;                                                             
        }                    

	union i2c_smbus_data data;
	struct i2c_smbus_ioctl_data args;
	int ret;
	data.byte = val;
	args.read_write = I2C_SMBUS_WRITE;
	args.command = reg;
	args.size = I2C_SMBUS_BYTE_DATA;
	args.data = &data;
	ret = ioctl(i2c1_fd, I2C_SMBUS, &args);
	if (ret!=0) 
	{
        	perror("ioctl");
        	return -1;
        }
	return data.word;
}

/*============================================================================
* Function      : i2c_read_short
* IN            : None
* OUT           : None
* RETURN        : 
* INFO          : I2C read short. 
============================================================================*/
signed short i2c_read_short(unsigned char deviceAddress, unsigned char reg, int i2c1_fd)
{
	                                                                                   
    if(ioctl(i2c1_fd, I2C_SLAVE, deviceAddress) < 0)                                   
    {                                                                                  
            printf("Eroror while I2C address 0x%x: %d error\n:", deviceAddress, errno);
            return -1;                                                        
    }                      
	union i2c_smbus_data data;
	struct i2c_smbus_ioctl_data args;
	int ret;
	args.read_write = I2C_SMBUS_READ;
	args.command = reg;
	args.size = I2C_SMBUS_WORD_DATA;
	args.data = &data;
	ret = ioctl(i2c1_fd, I2C_SMBUS, &args);
        if (ret!=0) 
	{
        	perror("short ioctl");
        	return -1;
        }
	return data.word;
}
