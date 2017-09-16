/*******************************************************************************
* FileName		: gpio.h
* Description	: This interface is used to initialize the
* 				  Email Data structures and variables.
*******************************************************************************/
#ifndef FGDRVERGOIO_H
#define FGDRVERGOIO_H
/*******************************************************************************
*******************************************************************************/
/*============================================================================*/
/* INCLUDES */
/*============================================================================*/
/*#include "fgMacros.h"
#include <stdio.h>
#include "fgErrorTypes.h"
#include "fgTypeDefs.h" */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<poll.h>
/*============================================================================*/
/* EXPORTED TYPES & DEFINES */
/*============================================================================*/

/*============================================================================*/
/*GLOBAL TYPES AND DEFINES*/
/*============================================================================*/

/*============================================================================*/
/* PRIVATE DATA */
/*============================================================================*/
/*============================================================================*/
/* EXPORTED FUNCTION PROTOTYPES */
/*============================================================================*/

/*==============================================================================
* @START
* Function:	pdSapiEmail_Init
* IN	:	gpio: the GPIO number
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: export the GPIO to user space
* @END
*============================================================================*/

int gpio_export(unsigned int gpio);

/*==============================================================================
* @START
* Function:	pdSapiEmail_Init
* IN	:	gpio: the GPIO number
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: unexport the GPIO to user space
* @END
*================================pio-test.c:18:0:
../include/gpio.h:102:5: error:============================================*/

int gpio_unexport(unsigned int gpio);

/*==============================================================================
* @START
* Function:	 gpio_set_dir
* IN	:	gpio: the GPIO number
* OUT 	: 	 out_flag: the flag of output or input.It's value can be 1 or 0.
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: set direction of GPIO
* @END
*============================================================================*/

int gpio_set_dir(unsigned int gpio ,int out_flag) ;

/*==============================================================================
* @START
* Function:	 gpio_set_value
* IN	:	gpio: the GPIO number
 *          value: the value of GPIO. Supports values of 0 and 1. 
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: set the value of GPIO
* @END
*============================================================================*/

int gpio_set_value(unsigned int gpio, unsigned int value) ;

/*==============================================================================
* @START
* Function:	 gpio_get_value
* IN	:	gpio: the GPIO number
 *          value: the value of GPIO. Supports values of 0 and 1. 
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: get the value of GPIO
* @END
*============================================================================*/

//int gpio_get_value(unsigned int gpio, unsigned int value);

/*==============================================================================
* @START
* Function:	 gpio_get_edge
* IN	:	gpio: the GPIO number
 *          edge that trigger interrupt 
* OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: set the edge that trigger interrupt
*============================================================================*/

int gpio_set_edge(unsigned int gpio ,char *edge);


/*==============================================================================
* @START
* Function:	 gpio_fd_open
* IN	:	gpio: the GPIO number
 * OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: pen gpio device and return the file descriptor
* @ENDo
*============================================================================*/

int gpio_fd_open(unsigned int gpio)  ;

/*==============================================================================
* @START
* Function:	 gpio_fd_close
* IN	:	gpio: the GPIO number
 * OUT 	: 	None
* PRE	:	None
* POST  :	None
* RETURN:
* INFO :  brief: close gpio device and return the file descriptor
* @END
*============================================================================*/

int gpio_fd_close(int fd)  ;


/* Test API */
void say_hello(void);


#endif
