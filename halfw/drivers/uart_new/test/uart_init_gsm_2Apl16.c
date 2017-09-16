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

#define GSM_ON 63
#define GSM_REG_ON 75
#define GSM_RESET 74
#define SIM_SEL 87 //GPIO3_23	

/* GSM receive handler */
void gsm_rx_hanlder(void);
/* Check the string present in the rx buffer */
int verify_response(char * rx_buff, char * check_str);
/* GSM Initialization */
void gsm_init(void);
/* Sending commands to gsm module */
int mdm_cmd_send(char *cmd, int length, int rx_cnt);

/* definition of signal handler */
void signal_handler_IO(int status);  
/*UART Initialization */
int init_testuart(void);

char rx_buff[rx_length] = {0};
int rx_flag = 0, count = 0;
int module_up = FALSE, module_init = FALSE;


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
    int z=0;

    if(ret != 0)
    {
    	printf("UART1 configured....\n");
        gpio_export(GSM_ON);
        gpio_export(GSM_REG_ON);
        gpio_export(GSM_RESET);
	gpio_export(SIM_SEL);

        gpio_set_dir(GSM_ON, OUT);
        gpio_set_dir(GSM_REG_ON, OUT);
        gpio_set_dir(GSM_RESET, OUT);
	gpio_set_dir(SIM_SEL, OUT);

        gpio_set_value(GSM_ON,0);
        for(z=0; z<15000; z++);
        gpio_set_value(GSM_ON,1);
        gpio_set_value(GSM_REG_ON,1);
	gpio_set_value(SIM_SEL,0);

//	sendport(fd, "FareGeo Technologies", strlen("FareGeo Technologies"));
    }else
    {
	printf("UART Init failed \n");
    }

    connected = 1;
    while(connected == 1)
    {
	if(rx_flag)
	{
		gsm_rx_hanlder();
		if((count >= 13) && (module_up == FALSE))
		{       /* Wait till the GSM module up to initialize the modem */
			printf("1. %s \n", rx_buff);
                        rx_buff[count] = '\0';
                        printf("2. %s \n", rx_buff);
			if(verify_response((char*) rx_buff, (char*) "SYSSTART") != 0);
			{
				printf("GSM MODULE is UP \n");
				module_up = TRUE;
				count = 0;	
				memset(rx_buff, 0, rx_length);
			}
		}else if((module_up == TRUE) && (module_init == FALSE))
		{
			/* Module is up now do the initializtaion */
			gsm_init();
			module_init = TRUE;
		}
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

int verify_response(char *rx_buff, char * check_str)
{
    //printf("Rxd_buf:%s Check Str:%s \n", rx_buff, check_str);
    if(strstr(rx_buff, check_str) != NULL)
    {
	return 1;
    }else
    {
	printf("Check Fail \n");
	return 0;
    }
}

void gsm_init(void)
{
    char attension[] = "AT\r";
    char echo[] = "ATE0\r";
    char cme_err[] = "AT+CMEE=1\r"; /* CMEE error message enable */
    char sim_presence[] = "AT+CPIN?\r";
    char signal_quality[] = "AT+CSQ\r";
    char reg_homeNW[] = "AT+CREG=1\r";
    char nw_reg_status[] = "AT+CREG?\r";
    char gprs_nw_reg[] = "AT+CGREG=1\r"; /* Packet Domain Network Registration Status GPRS */
    char gprs_nw_reg_status[] = "AT+CGREG?\r";

    mdm_cmd_send(echo, strlen(echo), 2);
    if(verify_response((char*) rx_buff, (char*) "OK") != 0);
    {
	printf("Echo Disabled \n");
    }
   
    mdm_cmd_send(attension, strlen(attension), 2);
    if(verify_response((char*) rx_buff, (char*) "OK") != 0);
    {
        printf("Attension OK \n");
    }

    mdm_cmd_send(cme_err, strlen(cme_err), 2);
    if(verify_response((char*) rx_buff, (char*) "OK") != 0) 
    {
        printf("Enable CME Error \n");
    }
 
    mdm_cmd_send(sim_presence, strlen(sim_presence), 12);
    if(verify_response((char*) rx_buff, (char*) "+CPIN: READY") != 0) 
    {
        printf("SIM is present in the module \n");
    }else
	printf("Please Insert the SIM card \n");

    mdm_cmd_send(signal_quality, strlen(signal_quality), 11);
    

    mdm_cmd_send(reg_homeNW, strlen(reg_homeNW), 2);
    if(verify_response((char*) rx_buff, (char*) "OK") != 0) 
    {
        printf("Registered to HOME network succesfully\n");
    }

    mdm_cmd_send(nw_reg_status, strlen(nw_reg_status), 10);
/*    if(verify_response((char*) rx_buff, (char*) "OK") != 0) 
    {
        printf("Attension OK \n");
    }
*/

    mdm_cmd_send(gprs_nw_reg, strlen(gprs_nw_reg), 2);
    if(verify_response((char*) rx_buff, (char*) "OK") != 0) 
    {
        printf("GPRS Network registration is DONE \n");
    }


    mdm_cmd_send(gprs_nw_reg_status, strlen(gprs_nw_reg_status), 11);
    /*if(verify_response((char*) rx_buff, (char*) "OK") != 0) 
    {
        printf("Attension OK \n");
    }
*/

}	

int mdm_cmd_send(char *cmd, int length, int rx_cnt)
{
//    int k=0;

//    memset(rx_buff, 0, rx_length); 
//    count = 0;

//    for(k=0; k<3; k++)
    {
	memset(rx_buff, 0, rx_length);
        count = 0;
        printf("cmd:%s \n", cmd);
	sendport(fd, cmd, length);
        sleep(3);
        /*do{
        	if(rx_flag)
		{
	   		gsm_rx_hanlder();
		}else
		{
	   		sleep(1);
		}	
	}while(count < rx_cnt);        
        */
        #if 0
        if((verify_response((char*) rx_buff, (char*) "OK")) != 0)
        {
                //printf("Module attension OK \n");
		break;
        }
	#endif

    }
}


