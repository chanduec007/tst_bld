/***********************************************************
 * PROJECT NAME: HMI Application Framework

 * Platform: BBB

 * @file: hal_spi.h

 * Function: SPI Interface module header APIs

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***********************************************************/
#ifndef SPI_MODULE_H
#define SPI_MODULE_H

#define SPI1_path       "/dev/spidev1.0"    
#define SPI2_path	"/dev/spidev1.1"
	
typedef enum {
	      spi1=1, 
	      spi2}spi_t;

int spi_init(spi_t spi_bus);


#endif
