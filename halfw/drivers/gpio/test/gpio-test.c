/********************************************************************
* 		copyright (C) 201 all rights reserved
*			 @file: gpio.c
* 		  @Created: 
* 	  	   @Author: 
* 	  @Description: test gpios interrupt 
*	  @Modify Date: 
*********************************************************************/

#include <gpio.h>

#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define OUT 1
#define IN 0
#define MAX_BUF 60


int main(int argc, char **argv)  
{  
    struct pollfd *fdset;  
    int nfds = 1;  
    int gpio_fd, timeout, rc;  
    char *buf[MAX_BUF];  
    unsigned int gpio;  
    int len;
    char *cmd;
    unsigned int value;
    int data = 0;
    int temp = 0xff;     
 
    say_hello();

    //printf("\n**************** WELCOME TO GPIO TEST ***************\n");

    fdset = (struct pollfd*)malloc(sizeof(struct pollfd));  
  
    if (argc < 3) {  
        printf("Usage: %s <gpio-pin> <direction> [value]\n\n", argv[0]);        
        exit(-1);  
    }
    cmd = argv[2];
    gpio = atoi(argv[1]);
    data = atoi(argv[3]);
    temp = gpio_export(gpio);
	
    printf("Testing:%s cmd:%s gpio-pin:%d value:%d \n\n", argv[0], cmd, gpio, data);

    if(strcmp(cmd, "interrupt") == 0) 
    {
    	printf("\n****************************GPIO interrupt*****************************\n");
		  
	gpio_set_dir(gpio, IN);  
	gpio_set_edge(gpio, "rising");  
	gpio_fd = gpio_fd_open(gpio);
		
	/* GPIO_LED configure */
	//gpio_export(GPIO_LED);  
	//gpio_set_dir(GPIO_LED, OUT);
		
	timeout = POLL_TIMEOUT;  
	   
	while (1) 
	{  
	    memset((void*)fdset, 0, sizeof(fdset)); 
	    fdset->fd = gpio_fd;  
	    fdset->events = POLLPRI;  
	
	    rc = poll(fdset, nfds, timeout);        
	    if (rc < 0) 
	    {  
	        printf("\npoll() failed!\n");  
	        return -1;  
	    }  
		    
	    if (rc == 0) 
	    {  
	       printf(".");
	        /* LED off */
	        //gpio_set_value(GPIO_LED, 1);  
	    }  
		          
	    if (fdset->revents & POLLPRI) 
  	    {  
	        len = read(fdset->fd, buf, MAX_BUF);  
	        printf("\nGPIO %d interrupt occurred\n", gpio);
	        /* when GPIO interrupt occurred, LED turn on */
		        //gpio_set_value(GPIO_LED, 0);  
	    }
	    fflush(stdout);   
	} 
	
	gpio_fd_close(gpio_fd); 
		   	
    }
    else if(strcmp(cmd, "out") == 0) 
    {
	printf("GPIO-OUT");
        gpio_set_dir(gpio, OUT);
		
  	if(argc = 4) 
	{
  	    gpio_set_value(gpio, atoi(argv[3]));
  	    printf("gpio%d is set to %d\n", gpio, atoi(argv[3]));	
  	}
    }
    else if(strcmp(cmd, "in") == 0) 
    {
  	printf("GPIO-IN");	
  	gpio_set_dir(gpio, IN);
  	printf("\n");
  	while (1) 
	{
  	    gpio_get_value(gpio, &value);
  	    printf("\rvalue:%d", value);
  	}
  		
    }
    else if(strcmp(cmd, "toggle") == 0) 
    {
        temp = gpio_set_dir(gpio, OUT);
	printf("GPIO:%d toggle\n", gpio);

        while(1) 
	{
            gpio_set_value(gpio, data);
            printf("gpio:%d is set to %d\n", gpio, data);
     	    sleep(1);
	    data = !data;
        }
     }
     else if(strcmp(cmd, "unexport") == 0) 
     {
  	gpio_unexport(gpio);	
     }
     else 
     {
  	printf("Usage: %s <gpio-pin> <direction> [value]\n\n", argv[0]);        
        exit(-1);	
     }
  	  	
     return 0;
}  

