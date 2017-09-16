/***********************************************************
 * PROJECT NAME: HMI Application Framework

 * Platform: BBB

 * @file: app_main.c

 * Function: Main Application Module 

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***********************************************************/
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
#include "uartlib.h"
#include "hal_uart.h"
 
signed short int x,y,z;
int i2c1_fd;

int main(void)
{	
	board_init();
	
	while(1)
	{
		printf("System is running in while loop\n");
		sleep(2);
	
		printf("***** ADXL345 Initialization *****\n");	
		x = i2c_read_short(ADXL_ADDRESS, DATAX0, i2c1_fd);
		y = i2c_read_short(ADXL_ADDRESS, DATAY0, i2c1_fd);
		z = i2c_read_short(ADXL_ADDRESS, DATAZ0, i2c1_fd);
		printf("x=%5d y=%5d z=%5d\n", x,y,z);

		printf("***** L3GD20H Initialization *****\n");	
		x = i2c_read_short(L3GD20H_ADDRESS, OUT_X_L, i2c1_fd);
		y = i2c_read_short(L3GD20H_ADDRESS, OUT_Y_L, i2c1_fd);
		z = i2c_read_short(L3GD20H_ADDRESS, OUT_Z_L, i2c1_fd);
 	       	printf("x=%5d y=%5d z=%5d\n",x,y,z);
	}	
	return 1;
}


int board_init(void)
{	
	i2c_init(i2c1);
	i2c1_fd = i2c_init(i2c1);
	adxl_init();
	l3gd20h_init();
	uart_init();	
	printf("Board Initialization is Completed.\n");
}



    		
