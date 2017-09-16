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


#define GNS_POWER_EN  91 	//GPIO3_27
#define GNS_RST_PIN   107 	//GPIO4_11

#define OUT 1

#define MAX_LEN 100
unsigned char rx_buff[MAX_LEN] = {0};
unsigned int rx_index = 0;
unsigned char adsb_mode2[] = {'#','4','2','-','0','0',0x0D};
unsigned char adsb_mode3[] = {'#','4','3','-','0','0',0x0D};
unsigned char adsb_reset[] = {'#','F','F',0x0D};

/* definition of signal handler */
void signal_handler_IO(int status);  
/*UARiT Initialization */
int init_testuart(void);
void rx_handle(void);


unsigned char data = 0, temp[2];
int n;
int fd;
int connected;
struct termios termAttr;
struct sigaction saio;

unsigned char rxd_flag = 0;

int main()
{
    int ret = 0, i;
	//unsigned char tx_buf[] = {'#','4','2','-','0','0',0x0D};

    ret = init_testuart();
    if(ret != 0)
    {
    	printf("UART9 configured....\n");
		gpio_export(GNS_POWER_EN);
   	    gpio_export(GNS_RST_PIN);

		gpio_set_dir(GNS_POWER_EN, OUT);
		gpio_set_dir(GNS_RST_PIN, OUT);

		gpio_set_value(GNS_RST_PIN,0);
		for(i=0; i<1000; i++);
    	gpio_set_value(GNS_RST_PIN,1);
		gpio_set_value(GNS_POWER_EN,1);
    }else
    {
		printf("UART Init failed \n");
    }

	//printf("Tx: %s \n", tx_buf);
	//sendport(fd, tx_buf, strlen(tx_buf));

	printf("Setting GNS to mode2: %s \n", adsb_mode2);
    sendport(fd, adsb_mode2, strlen(adsb_mode2));

    connected = 1;
    while(connected == 1)
	{
	 rx_handle();
	 sleep(1);
#if 0
	 printf("Reset ADSB:%s \n", adsb_reset);
	 sendport(fd, adsb_reset, strlen(adsb_reset));
	 for(i=0; i<10000; i++);
	 printf("Tx: %s \n", adsb_mode2);
	 sendport(fd, adsb_mode2, strlen(adsb_mode2));
	 for(i=0; i<20000; i++);
	 //printf("Tx: %s \n", adsb_mode3);
     //sendport(fd, adsb_mode3, strlen(adsb_mode3));
	 //for(i=0; i<60000; i++);
#endif    
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
     cfsetispeed(&termAttr,B921600);
     cfsetospeed(&termAttr,B921600);
     termAttr.c_cflag &= ~PARENB;
     termAttr.c_cflag &= ~CSTOPB;
     termAttr.c_cflag &= ~CSIZE;
     termAttr.c_cflag |= CS8;
     termAttr.c_cflag |= (CLOCAL | CREAD);
     termAttr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
     termAttr.c_iflag &= ~(IXON | IXOFF | IXANY);
     termAttr.c_oflag &= ~OPOST;
     configport(fd, &termAttr);
 	 //printf("Tx: %s \n", tx_buf);
	 //sendport(fd, adsb_mode2, strlen(tx_buf));
    return fd;
}

/* do the receiver based functionality here */
void signal_handler_IO (int status)
{

#if 0
    int ret = -1;
    /*In this test application received byte will be transmitting again*/
    ret=readport_buf(fd, &rx_buff[rx_index++], 1);
    if(rx_index >= MAX_LEN)
		rx_index = 0;

	printf("Rxd_Byte: %c\n", rx_buff[rx_index-1]);
    //temp[0] = data;
    //sendport(fd, temp, strlen(temp));
    //data = 0;
#else
	rxd_flag = 1;
#endif
}
 
void rx_handle(void)
{
	int ret = 0;
	
	if(rxd_flag)
	{
		ret=readport_buf(fd, &rx_buff[rx_index++], 1);
	    if(rx_index >= MAX_LEN)
    	    rx_index = 0;

    	printf("Rxd_Byte: %c\n", rx_buff[rx_index-1]);

	}else
	{
		printf("GNS: nothing rxd \n");
	}
}

