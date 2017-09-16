
/*
 * PROJECT NAME: Application Library
 * Platform: BB
 * @file: udp_serv.c
 * @brief: 
 * Function: comm module
 * Created on: 09/June/2017
 * Revision-Date: 0.1 - 27/June/2017
 * Author: FGT
 */

#include "os_includes.h"
#include "dblog.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "cmdef.h"

#define RECV_LEN 512
#define SEND_LEN 512
#define UDP_PORT 8888

char recv_buf[RECV_LEN];
char send_buf[SEND_LEN];
int ssid, port_num;
int recv_len = 0, send_len = 0;
struct sockaddr_in si_me, si_other;


int main(void)
{
    int result = OP_FAILURE;
	int slen = sizeof(si_other);
    //getaddrinfo

    ssid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(ssid < 0)
    {
        debug_log(D2SCRN, "socket open error");
        return result;
    } 
	debug_log(D2SCRN, "socket open success");

	memset ((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(UDP_PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(ssid, (struct sockaddr *)&si_me, sizeof(si_me)) < 0)
	{
        debug_log(D2SCRN, "bind error");
	}
	debug_log(D2SCRN, "socket bind success");
	
	while(1)
	{
		if(recv_len = recvfrom(ssid, recv_buf, RECV_LEN, 0, 
			(struct sockaddr *)&si_other, &slen) < 0)
		{
            debug_log(D2SCRN, "recv error");
			
		}
	    debug_log(D2SCRN, "recv packet from %s:%d", 	
		inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	    debug_log(D2SCRN, "recv data: %s\n", recv_buf); 

	}
	
	if(sendto(ssid, send_buf, send_len, 0, 
		(struct sockaddr *)&si_other, slen) < 0)
	{
 		debug_log(D2SCRN, "send error");
	}
	

}
