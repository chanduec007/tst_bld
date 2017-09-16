/*
* uartlib.c
*
* UART Library
* Faregeo Technologies test application
*
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uartlib.h"


//struct termios oldtio;

/*************************************************
*               UART FUNCTIONS                   *
*************************************************/

/* OPEN PORT */
int openport(char port[])
{
	int fd=0;

	fd = open(port, O_RDWR | O_NOCTTY |O_NDELAY ); /* Open in non blocking read/write mode */
	//printf ("This is %d %d \n", port,fd);
	/*O_NOCTTY - When set and port identifies a terminal device, open() shall not cause the terminal device to become the controlling 		terminal for the process */

	/* O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a 		failure status if there is no input immediately available (instead of blocking). Likewise, write requests can also return
	immediately with a failure status if the output can't be written immediately. */

	if (fd < 0)
	{
		DEBUG_INFO("Failed to open the port!!!\n");  
		exit(1);      
	}

	return fd;
}

/* CONFIGURE PORT */
void configport(int fd, struct termios *newtio)
{
//	fcntl(fd, F_SETFL, 0); /* This effectly clears all flags on the file descriptor */

	//tcgetattr(fd, &oldtio); /* save current serial port settings */
        //bzero(&newtio, sizeof(newtio)); /* clear structure for new port settings */
        
	/* 
          now clean the modem line and activate the new settings for the port
        */
	//tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, newtio); /* TCSANOW : the change occurs immediately */
}                                                                    

/* WRITE PORT */
void sendport(int fd, char string[], int length)
{
	int tx_length = 0;

	DEBUG_INFO("Start sending.:%s \n", string);
	
	tx_length = write(fd, string, length);

	if (tx_length < 0)
	{
		DEBUG_INFO("Data write failed!!!\n");
		exit(1);
	}
	else
	{
//		DEBUG_INFO("Data sent successfully : %d bytes written\n",tx_length);
	}
}

/* READ PORT */
unsigned char readport(int fd)
{
#if 0
	unsigned char buf[1]={0};
   	int rx_length = 0;

	DEBUG_INFO("Start reading......\n");

        rx_length = read(fd, &buf, 1);

	if (rx_length < 0)
	{
		DEBUG_INFO("Data read failed!!!\n");
			exit(1);
	}

	//DEBUG_INFO("%i bytes read : %s\n", rx_length, rx_buffer);
#endif

	unsigned char rx_buffer[255];
	unsigned char buf=0;
	int rx_length=0;

	DEBUG_INFO("Please enter the data. To exit press Enter\n");

	DEBUG_INFO("Start reading......\n");

	while(1)
	{
		rx_length = read(fd, &buf, 1);

		/*if (rx_length < 0)
		{
			DEBUG_INFO("Data read failed!!!\n");
			exit(1);
		}*/

		if(rx_length == 1)/*(buf == '\n')*/
			break;

		rx_buffer[rx_length++]=buf;	
	}
	rx_buffer[rx_length]='\0';
	
	DEBUG_INFO("%i bytes read : %s\n", rx_length, rx_buffer);

	return buf;
}

/* READ PORT BUFFER DATA */
int readport_buf(int fd, unsigned char *rx, int length)
{
	unsigned char buf = 0;
	int rx_length = 0;
	int ret = -1;

//        DEBUG_INFO("Start reading..\n");

	while(length)
	{
		ret = read(fd, &buf, 1);

        	if (ret < 0)
        	{
                	DEBUG_INFO("Data read failed!!!\n");
                        exit(1);
		}
		*rx++ = buf;
		//*rx = buf;
		//DEBUG_INFO("ReadByte:%c \n", *rx++);
		length--;	        	
		
	}
	return ret;

}


/* CLOSE PORT */
void closeport(int fd)
{
	/* restore the old port settings */
        //tcsetattr(fd, TCSANOW, &oldtio); /* TCSANOW : the change occurs immediately */
	close(fd);

}


