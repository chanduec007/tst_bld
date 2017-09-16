/*
* uartlib.h
* Faregeo Technologies test application
*/

#ifndef _Included_com_gpiolib
#define _Included_com_gpiolib
#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG

#ifdef DEBUG
#define DEBUG_INFO(fmt, args...) printf(fmt, ## args)
#else
#define DEBUG_INFO(fmt, args...)
#endif

#define BAUDRATE	B115200
#define _POSIX_SOURCE	1 /* POSIX compliant source */
#define FALSE		0
#define TRUE		1
#define SUCCESS		0
#define FAILURE 	1
#define ONE_SEC 	1

int openport(char port[]);
void configport(int fd, struct termios *newtio);
void sendport(int fd, char string[], int length);
unsigned char readport(int fd);
void closeport(int fd);
int readport_buf(int fd, unsigned char *rx, int length);


#ifdef __cplusplus
}
#endif
#endif
