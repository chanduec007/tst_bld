/***********************************************************
 * PROJECT NAME: HMI Test Framework

 * Platform: BBB

 * @file: hal_uart.c

 * Function: UART Interface module 

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
#include <fcntl.h>
//#include "gpio.h"
#include "uartlib.h"
#include "hal_uart.h"

/* Global variables */
unsigned char data = 0, temp[2];
int n;
int fd;
struct termios termAttr;
struct sigaction saio;

/*============================================================================
* Function	: uart_init
* IN    	: None
* OUT   	: None
* RETURN	: 
* INFO 		: initialize the uart. 
*============================================================================*/
int uart_init(uart_t uart_port, int stop_bit, int data_bit, int * uart_handler)
{
	printf("Uart Initialization...\n");
	if(uart_port == uart1)
	{
		fd = open(UART1, O_RDWR | O_NOCTTY | O_NDELAY);
	}
	else if (uart_port == uart2)
	{
		fd = open(UART2, O_RDWR | O_NOCTTY | O_NDELAY);
	}
	

	if(stop_bit == 1)
	{
		termAttr.c_cflag &= ~CSTOPB; 
	}	


	if(data_bit == 8)           
        {                                                            
        	termAttr.c_cflag |= CS8; 

	}     
	
	
    /* This effectly clears all flags on the file descriptor */
     fcntl(fd, F_SETFL, 0);     

     /* Configure the Rx line signal handler*/
     saio.sa_handler = uart_handler;
     saio.sa_flags = 0;
     saio.sa_restorer = NULL; 
     sigaction(SIGIO,&saio,NULL);

     fcntl(fd, F_SETFL, FNDELAY);
     fcntl(fd, F_SETOWN, getpid());
     fcntl(fd, F_SETFL,  O_ASYNC ); 

     /* Configuring the test UART */
     tcgetattr(fd,&termAttr);
     cfsetispeed(&termAttr,B115200);
     cfsetospeed(&termAttr,B115200);
     termAttr.c_cflag &= ~PARENB;
//     termAttr.c_cflag &= ~CSTOPB;
     termAttr.c_cflag &= ~CSIZE;
//     termAttr.c_cflag |= CS8;
     termAttr.c_cflag |= (CLOCAL | CREAD);
     termAttr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
     termAttr.c_iflag &= ~(IXON | IXOFF | IXANY);
     termAttr.c_oflag &= ~OPOST;
     configport(fd, &termAttr);
     return fd;
}


void uart_handler(int status)
{
    int ret = -1;
    /*In this test application received byte will be transmitting again*/
    ret=readport_buf(fd, &data, 1);
    printf("Rxd_Byte: %c\n", data);
    temp[0] = data;
    sendport(fd, temp, strlen(temp));
    data = 0;
}



