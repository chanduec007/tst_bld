/**************************************************
 * PROJECT NAME: HMI Application Framework

 * Platform: BBB

 * @file: app_sensors.c

 * Function: Sensors module 

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <errno.h>
#include <termios.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <poll.h>
#include "hal_i2c.h"
#include "app_sensors.h"

int i2c1_fd;
/**************************************************
	  ADXL345 Initialization
***************************************************/
int adxl_init(void)                                    
{                                                     
	int ret = 0;                                 
                                                     
	ret = ioctl(i2c1_fd, I2C_SLAVE, ADXL_ADDRESS);
                                                      
	ret = i2c_read(ADXL_ADDRESS, DEVID, i2c1_fd);                         
	printf("ID[0x%02x]=0x%02x\n", DEVID, ret);             
                                                               
	i2c_write(ADXL_ADDRESS, POWER_CTL, 0x28, i2c1_fd);                   
}                


/**************************************************
          L3GD20H Initialization
***************************************************/
int l3gd20h_init(void)	
{
	if(i2c_read(L3GD20H_ADDRESS, WHO_AM_I, i2c1_fd)!=0xD7)
        {
                printf("ERROR communicating with L3GD20H !\n");
                return -1;
        }
	
        // Enable x,y,z and turn off power down: 
        i2c_write(L3GD20H_ADDRESS, CTRL_REG1, 0x0F, i2c1_fd);

        // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
        i2c_write(L3GD20H_ADDRESS, CTRL_REG2, 0x00 , i2c1_fd);

        // Configure CTRL_REG3 to generate data ready interrupt on INT2
        // No interrupts used on INT1, if you'd like to configure INT1
        // or INT2 otherwise, consult the datasheet: 
        i2c_write(L3GD20H_ADDRESS, CTRL_REG3, 0x08,  i2c1_fd);

        // CTRL_REG4 controls the full-scale range, among other things:
        i2c_write(L3GD20H_ADDRESS, CTRL_REG4, 0x20, i2c1_fd);

        // CTRL_REG5 controls high-pass filtering of outputs, use it if you'd like:
        i2c_write(L3GD20H_ADDRESS, CTRL_REG5, 0x00 , i2c1_fd);

}



