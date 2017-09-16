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


/* definition of signal handler */
void signal_handler_IO(int status);  
/*UART Initialization */
int init_testuart(void);


unsigned char data = 0, temp[2];
int n;
int fd;
int connected;
struct termios termAttr;
struct sigaction saio;

int main()
{
    int ret = 0;
    ret = init_testuart();
    if(ret != 0)
    {
    	printf("UART1 configured....\n");
		//gpio_set_dir(GNS_POWER_EN, OUT);
		//gpio_set_dir(GNS_RST_PIN, OUT);

		//gpio_set_value(GNS_POWER_EN,1);
    }else
    {
		printf("UART Init failed \n");
    }

    connected = 1;
    while(connected == 1){
		printf("Testing UART \n");
		sleep(2);
		// some code
    }
    close(fd);
    exit(0);             
}

int init_testuart(void)
{
     fd = open("/dev/ttyO0", O_RDWR | O_NOCTTY | O_NDELAY);
     if (fd == -1)
     {
        perror("open_port: Unable to open /dev/ttyO0\n");
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
     cfsetispeed(&termAttr,B115200);
     cfsetospeed(&termAttr,B115200);
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
    int ret = -1;
    /*In this test application received byte will be transmitting again*/
    ret=readport_buf(fd, &data, 1);
    printf("Rxd_Byte: %c\n", data);
    temp[0] = data;
    sendport(fd, temp, strlen(temp));
    data = 0;

}
 
