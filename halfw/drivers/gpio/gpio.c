/********************************************************************
* 		copyright (C) 2014 all rights reserved
*			 @file: gpio.c
* 		  @Created: 2014-8-6 15:00
* 	  	   @Author: conway chen
* 	  @Description: test gpios interrupt 
*	  @Modify Date: 2014-8-6 15:00
*********************************************************************/
#include <gpio.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define GPIO_LED 41
#define MAX_BUF 60
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define OUT 1
#define IN 0



/** 
 * brief: export the GPIO to user space
 * @Param: gpio: the GPIO number
 */
int gpio_export(unsigned int gpio)
{
	int fd ,len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/export" ,O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf ,sizeof(buf) ,"%d" ,gpio);
	write(fd ,buf ,len);
	close(fd);
	return 0;
}


/** 
 * brief: unexport the GPIO to user space
 * @Param: gpio: the GPIO number
 */  
int gpio_unexport(unsigned int gpio)
{
	int fd ,len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/unexport" ,O_WRONLY);
	if (fd < 0) {
		perror("gpio/unexport");
		return fd;
	}
	len = snprintf(buf ,sizeof(buf) ,"%d" ,gpio);
	write(fd ,buf ,len);
	close(fd);
	return 0;
}

/** 
 * brief: configure GPIO for input or output
 * @Param: gpio: the GPIO number
 * @Param: out_flag: the flag of output or input.It's value can be 1 or 0.  
 */ 
int gpio_set_dir(unsigned int gpio ,int out_flag)
{
	int fd ,len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", gpio);
	fd = open(buf ,O_WRONLY);
	if (fd < 0) {
		perror(buf);
		return fd;
	}
	if (out_flag) 
		write(fd ,"out" ,4);
	else 
		write(fd ,"in" ,3);
	close(fd);
	return 0;
}

/** 
 * brief: Set the value of GPIO 
 * @Param: gpio: the GPIO number
 * @Param: value: the value of GPIO. Supports values of 0 and 1. 
 */  
int gpio_set_value(unsigned int gpio, unsigned int value)  
{  
    int fd, len;  
    char buf[MAX_BUF];  
   
    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);      
    fd = open(buf, O_WRONLY);
	if (fd < 0) {  
        perror("gpio/set-value");  
        return fd;  
    }  
   
    if (value)  
        write(fd, "1", 2);  
    else  
        write(fd, "0", 2);  
   
    close(fd);  
    return 0;  
}

/** 
 * brief: get the value of GPIO
 * @Param: gpio: the GPIO number
 * @Param: value: pointer to the value of GPIO
 */
int gpio_get_value(unsigned int gpio, unsigned int *value)
{
	int fd, len;
	char ch;
	char buf[MAX_BUF];

	len = snprintf(buf ,sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value" ,gpio); 
	fd = open(buf ,O_RDONLY);
	if (fd < 0) {
		perror("gpio_get_value");
		return fd;
	}
	read(fd ,&ch ,1);
	if (ch == '1') 
		*value = 1;
	else if(ch == '0') 
			*value = 0;
	close(fd);
	return 0;
}

/** 
 * brief: set the edge that trigger interrupt
 * @Param: gpio: the GPIO number
 * @Param: edge:  edge that trigger interrupt
 */
int gpio_set_edge(unsigned int gpio ,char *edge)
{
	int fd ,len;
	char buf[MAX_BUF];

	len = snprintf(buf ,sizeof(buf) ,SYSFS_GPIO_DIR "/gpio%d/edge" ,gpio);
	fd = open(buf ,O_WRONLY);
	if (fd < 0) {
		perror("gpio_set_edge");
		return fd;
	}
	write(fd ,edge ,strlen(edge) + 1);
	close(fd);
	return 0;
}

/** 
 * brief: open gpio device and return the file descriptor
 * @Param: gpio: the GPIO number
 */  
int gpio_fd_open(unsigned int gpio)  
{  
    int fd, len;  
    char buf[MAX_BUF];  
  
    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);  
   
    fd = open(buf, O_RDONLY | O_NONBLOCK );  
    if (fd < 0) {  
        perror("gpio/fd_open");  
    }  
    return fd;  
}  
  
/** 
 * brief: close gpio device 
 * @Param: fd: the file descriptor of gpio
 */
int gpio_fd_close(int fd)  
{  
    return close(fd);  
}  
  
void say_hello(void)
{
    printf(" ************ HELLO ************ \n");
    printf(" WELCOME TO FAREGEO TECHNOLOGIES \n");
    printf(" ****** LETS TEST THE GpIo ***** \n");
}
