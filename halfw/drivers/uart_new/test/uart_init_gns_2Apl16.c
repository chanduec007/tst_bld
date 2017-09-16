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

#define TRUE 1
#define FALSE 0

#define OUT 1
#define rx_length 50

#define GNS_ON 89    //GPIO3_25
#define GNS_RESET 90 //GPIO3_26
	

/* GNS receive handler */
void gns_rx_hanlder(void);

/* definition of signal handler */
void signal_handler_IO(int status);  
/*UART Initialization */
int init_testuart(void);
unsigned char adsb_mode2[] = {'#','4','2','-','0','0',0x0D};
unsigned char adsb_mode3[] = {'#','4','3','-','0','0',0x0D};
unsigned char adsb_reset[] = {'#','F','F',0x0D};


char rx_buff[rx_length] = {0};
int rx_flag = 0, count = 0;

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
    int i=0;

    if(ret != 0)
    {
    	printf("UART9 configured....\n");
        gpio_export(GNS_ON);
        gpio_export(GNS_RESET);
   
        gpio_set_dir(GNS_ON, OUT);
        gpio_set_dir(GNS_RESET, OUT);

        gpio_set_value(GNS_ON,1);
        gpio_set_value(GNS_RESET,1);
    	
    }else
    {
	    printf("UART Init failed \n");
    }

    connected = 1;

	printf("Reset ADSB:%s \n", adsb_reset);
    sendport(fd, adsb_reset, strlen(adsb_reset));
    for(i=0; i<10000; i++);
    printf("Tx: %s \n", adsb_mode2);
    sendport(fd, adsb_mode2, strlen(adsb_mode2));
    for(i=0; i<20000; i++);

    while(connected == 1)
    {
    	if(rx_flag)
   		{

		}
	
    }
    close(fd);
    exit(0);             
}

int init_testuart(void)
{
     fd = open("/dev/ttyO8", O_RDWR | O_NOCTTY | O_NDELAY);
     if (fd == -1)
     {
        perror("open_port: Unable to open /dev/ttyO8\n");
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
	rx_flag = 1;
}
    
void gsm_rx_hanlder(void)
{
    int ret = -1;
     
    //rx_flag = 0;    
    ret=readport_buf(fd, &data, 1);
    rx_buff[count] = data;
    //printf("Rxd_Byte: %c\n", data);
    printf("Rxd: %c\n", rx_buff[count]);
    if(count == rx_length)
    {
		count = 0;
    }else
    {
		count++;
    }
    data = 0;
    //rx_flag = 0;
}


