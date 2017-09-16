
/*
 * PROJECT NAME: Application Library
 * Platform: BB
 * @file: udp_client.c
 * @brief: 
 * Function: comm module
 * Created on: 27/June/2017
 * Revision-Date: 
 * Author: FGT
 */
#include "os_includes.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "appmn.h"
#include "dblog.h"
#include "cmdef.h"
#include "../cserv.h"


#define RECV_LEN 512
#define SEND_LEN 512

char recv_buf[RECV_LEN];
char send_buf[SEND_LEN];
int csid, port_num;
int recv_len = 0, send_len = 0;
struct sockaddr_in si_other, si_me;


int main(void)
{
    int result = OP_FAILURE;
	int slen = sizeof(si_other);
    //getaddrinfo

    csid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(csid < 0)
    {
        debug_log("client socket open error \n");
        return result;
    } 
	debug_log("client socket open success \n");
	memset ((char *) &si_me, 0, slen);

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(CLI_PORT);
	#if 1
		si_me.sin_addr.s_addr = inet_addr(LHOST);
	#else
		si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	#endif

	if(bind(csid, (struct sockaddr *)&si_me, sizeof(si_me)) < 0)
	{
        debug_log("test: cli sk bind error");
		//set_system_state(LHOST, SOCK_ERR);
        return result;
	}

	memset ((char *) &si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(SRV_PORT);
	si_other.sin_addr.s_addr = inet_addr(LHOST);

	#if 0
	if (inet_aton(SERVER, &si_other.sin_addr) == 0)
	{
        debug_log("client sock addr bind err\n");
	}
	#endif
	
	while(1)
	{
		memset(send_buf, 0, SEND_LEN);
		memcpy(send_buf, "ping from client: hello", sizeof(send_buf));
		
		if(sendto(csid, send_buf, strlen(send_buf), 0, 
			(struct sockaddr *)&si_other, slen) < 0)
		{
 			debug_log("client sock send error");
		}

		memset(recv_buf, 0, RECV_LEN);
		if(recv_len = recvfrom(csid, recv_buf, RECV_LEN, 0, 
			(struct sockaddr *)&si_other, &slen) < 0)
		{
            debug_log("client sock recv error");
			
		}
		puts(recv_buf);
	    debug_log("recv packet from %s:%d", 	
			inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	    debug_log("recv data: %s\n", recv_buf); 

	}
	
	

}
