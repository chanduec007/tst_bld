/***********************************************************
 * PROJECT NAME: HMI Application Framework

 * Platform: BBB

 * @file: hal_spi.c

 * Function: SPI Interface module 

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***********************************************************/
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <hal_spi.h>

/*============================================================================
* Function      : spi_init
* IN            : None
* OUT           : None
* RETURN        : 
* INFO          : initialize the I2C. 
============================================================================*/
int spi_init(spi_t spi_bus)
{
	int spi1_fd;
	int ret = 0;
	
	if(spi_bus == spi0)
        {
		spi1_fd = open(SPI0_path, O_RDWR);
	}
	else if (spi_bus == spi1)
	{
		spi1_fd = open(SPI1_path, O_RDWR);
	}




}







