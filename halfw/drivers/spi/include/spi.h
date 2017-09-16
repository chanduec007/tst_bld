/*******************************************************************************
* FileName		: spi.h
* Description	: 
*******************************************************************************/
#ifndef FGDRVERSPI_H
#define FGDRVERSPI_H
/*******************************************************************************
*******************************************************************************/
/*============================================================================*/
/* INCLUDES */
/*============================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/*============================================================================*/
/* EXPORTED TYPES & DEFINES */
/*============================================================================*/

/*============================================================================*/
/*GLOBAL TYPES AND DEFINES*/
/*============================================================================*/
struct spi_prms{
    unsigned char mode;
    unsigned char bits;
    unsigned int speed;
    unsigned short delay;
};

/*============================================================================*/
/* PRIVATE DATA */
/*============================================================================*/
/*============================================================================*/
/* EXPORTED FUNCTION PROTOTYPES */
/*============================================================================*/

/*==============================================================================
* @START
* Function:	fd_open
* IN	:	spi number
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: open spi device and return the file descriptor
* @ENDo
*============================================================================*/

int spi_fd_open(char* device)  ;

/*==============================================================================
* @START
* Function:	 spi_fd_close
* IN	:	fd:  fd number
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: close spi device and return the file descriptor
* @END
*============================================================================*/

int spi_fd_close(int fd)  ;



/*==============================================================================
* @START
* Function:	 spi_transfer
* IN	:	fd:  fd number, spi struct, txbuff, rxbuff, length
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: transfer
* @END
*============================================================================*/

int spi_transfer(int fd, struct spi_prms *spi, uint8_t *txbuff, uint8_t *rxbuff, int length);



/*==============================================================================
* Function:  spi_init
* IN    :   fd:  fd number
* OUT   :   None
* PRE   :   None
* POST  :   None
* RETURN:
* INFO :  brief: Configure the SPI
* @END
*============================================================================*/

int spi_init(int fd, struct spi_prms *spi)  ;


void pabort(const char *s);


#endif
