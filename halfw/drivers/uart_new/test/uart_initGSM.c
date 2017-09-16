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
#define GSM_ON 63
#define GSM_REG_ON 75
#define GSM_RESET 74

char at[] = "AT\r";
char ate[] = "ATE1\r";

/* definition of signal handler */
void signal_handler_IO(int status);  
/*UART Initialization */
int init_testuart(void);
void handle_rx(void);
void gsm_init(void);

int receive_flag = 0;
unsigned char data = 0, temp[2], rx_buff[10] = {0};
int n;
int fd;
int connected, count = 0;
struct termios termAttr;
struct sigaction saio;

int main()
{
    int ret = 0;
    ret = init_testuart();
    if(ret != 0)
    {
    	printf("UART1 configured....\n");
                gpio_export(GSM_ON);
                gpio_export(GSM_REG_ON);
		gpio_export(GSM_RESET);

                gpio_set_dir(GSM_ON, OUT);
                gpio_set_dir(GSM_REG_ON, OUT);
		gpio_set_dir(GSM_RESET, OUT);

                gpio_set_value(GSM_ON,1);
                gpio_set_value(GSM_REG_ON,1);
		//gpio_set_value(GSM_RESET,1);
		//sleep(1);
		//gpio_set_value(GSM_RESET,0);
		//sleep(1);
		//gpio_set_value(GSM_RESET,1);
 	 	//sleep(1);
                /*gpio_set_value(GSM_RESET,0);
		sleep(1);
                gpio_set_value(GSM_RESET,1);*/
		
		sleep(10);
		printf("GSM Reset Done..\n");
    }else
    {
                printf("UART Init failed \n");
    }
/*		sleep(10);
                printf("Sending AT: %s \n", at);
                sendport(fd, at, strlen(at));
		sleep(2);
                printf("Sending ATE0: %s \n", ate);
                sendport(fd, ate, strlen(ate));
*/
		//gpio_set_dir(GNS_POWER_EN, OUT);
		//gpio_set_dir(GNS_RST_PIN, OUT);

		//gpio_set_value(GNS_POWER_EN,1);
    sleep(5);

    //gsm_init();
    connected = 1;
    while(connected == 1)
    {
	    if(receive_flag)
	    {
		handle_rx();
	    }
	    else
	    {
//	   	printf("AT: %s \n", at);
//	    	sendport(fd, at, strlen(at));
            
	    	//printf("Testing UART \n");
//	    	sleep(1);
	    }

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
#if 1
    receive_flag = 1;
#else
    int ret = -1;
    /*In this test application received byte will be transmitting again*/
    ret=readport_buf(fd, &data, 1);
    printf("Rxd: %c\n", data);
    //temp[0] = data;
    //sendport(fd, temp, strlen(temp));
    //data = 0;
#endif
}

void handle_rx(void)
{
    int ret = -1;

//    printf("RxH: \n");
    if(receive_flag)
    {
//	printf("RxH: \n");
	receive_flag = 0;
      /*In this test application received byte will be transmitting again*/
//      ret=readport_buf(fd, &data, 1);
	ret=readport_buf(fd, &rx_buff[count], 1);
	printf("Rxd: %c\n", rx_buff[count]);
	if(count == 9)
	{
 	  count = 0;
	}else
	{
	  count++;
	}
	 
      //printf("Rxd: %c\n", rx_buff[count]);
      //receive_flag = 0;
    }else
    {
	//printf("No \n");
    }    
}

void gsm_init(void)
{
   unsigned char sim_present[] = "AT+CPIN?";	
   unsigned char sig_qulity[] = "AT+CSQ";
    
   printf("AT: %s \n", at);
   sendport(fd, at, strlen(at));
   sleep(2);
   printf("Sim Present: %s \n", sim_present);
   sendport(fd, sim_present, strlen(sim_present));   
   sleep(2);
} 
