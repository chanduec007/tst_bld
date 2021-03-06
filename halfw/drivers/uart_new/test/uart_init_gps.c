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
#include <gpio.h>
#include "uartlib.h"

#define OUT 1

#define GPS_ON 198
#define GPS_EN 72
#define GPS_RST 73

/* definition of signal handler */
void signal_handler_IO(int status);  
/*UART Initialization */
int init_testuart(void);

unsigned char data = 0, temp[2];
unsigned char rx_buf[100];

int n;
int fd;
int connected;
struct termios termAttr;
struct sigaction saio;
int uart_rx_flag = 0, recv_count = 0;
//unsigned char at[] = "AT";


void check_uart()
{
	int ret = 0;

	if(uart_rx_flag)
	{
		uart_rx_flag = 0;
		//for(count = 0; count < 10; count++)
		{
			//readport(fd);  
			ret = readport_buf(fd, &rx_buf[recv_count], 1);
//			ret = readport_buf(fd, &data, 1);
			printf("uart recv buf: %c \n",  rx_buf[recv_count]/*data*/);
			recv_count++;
			if (recv_count >= 100)
			{
				recv_count = 0;
			}
			//sleep(1);
		}
	} else
	{
		printf("nothing rxd\n");
	}
}

int main()
{
    int ret = 0;
    ret = init_testuart();
    if(ret != 0)
    {
    	printf("UART5 configured....\n");
	gpio_export(GPS_ON);
	gpio_export(GPS_EN);
	gpio_export(GPS_RST);

	gpio_set_dir(GPS_ON, OUT);
	gpio_set_dir(GPS_EN, OUT);
	gpio_set_dir(GPS_RST, OUT);

	gpio_set_value(GPS_ON,1);
	gpio_set_value(GPS_EN,1);
	gpio_set_value(GPS_RST,0);
    }else
    {
		printf("UART Init failed \n");
    }

#if 1
	while(1)
	{
//		sendport(fd, at, strlen(at));
		check_uart();
		sleep(1);
	}
#else
    connected = 1;
    while(connected == 1){
		printf("Testing UART \n");
		sleep(2);
		// some code
    }
    close(fd);
    exit(0);             
#endif
}

int init_testuart(void)
{
     fd = open("/dev/ttyO4", O_RDWR | O_NOCTTY | O_NDELAY);
     if (fd == -1)
     {
        perror("open_port: Unable to open /dev/ttyO4\n");
        exit(1);
     }

     /* This effectly clears all flags on the file descriptor */
     fcntl(fd, F_SETFL, 0);     

     /* Configure the Rx line signal handler*/
     saio.sa_handler = signal_handler_IO;
     saio.sa_flags = 0;
     saio.sa_restorer = NULL; 
     sigaction(SIGIO,&saio,NULL);

     fcntl(fd, F_SETFL, FNDELAY);
     fcntl(fd, F_SETOWN, getpid());
     fcntl(fd, F_SETFL,  O_ASYNC ); 

     /* Configuring the test UART4 */
     tcgetattr(fd,&termAttr);
     cfsetispeed(&termAttr,B9600);
     cfsetospeed(&termAttr,B9600);
     termAttr.c_cflag &= ~PARENB;
     termAttr.c_cflag &= ~CSTOPB;
     termAttr.c_cflag &= ~CSIZE;
     termAttr.c_cflag |= CS8;
     termAttr.c_cflag |= (CLOCAL | CREAD);
     termAttr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
     termAttr.c_iflag &= ~(IXON | IXOFF | IXANY);
     termAttr.c_oflag &= ~OPOST;
     configport(fd, &termAttr);
     return fd;
}

/* do the receiver based functionality here */
void signal_handler_IO (int status)
{
    uart_rx_flag = 1;

    /*In this test application received byte will be transmitting again*/

#if 0
    int ret = -1;
    ret = readport_buf(fd, &data, 1);
    printf("Rxd_Byte: %c\n", data);
    temp[0] = data;
    sendport(fd, temp, strlen(temp));
    data = 0;
#endif

}
 
