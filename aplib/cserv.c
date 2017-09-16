
/*
 * PROJECT NAME: Application Library
 * Platform: BB
 * @file: cserv.c
 * @brief: 
 * Function: comm module
 * Created on: 09/June/2017
 * Revision-Date: 0.1 - 27/June/2017
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
#include "cserv.h"

const char LHOST[] = "127.0.0.1";
//skb2u_t skb2u;
struct sockaddr_in si_b2u, si_sendto;

int init_cli_send()
{
	int result = OP_FAILURE;
	int slen = sizeof(si_sendto);

	debug_log("skb: client socket init \n");

	memset ((char *) &si_sendto, 0, slen);

	si_sendto.sin_family = AF_INET;
	si_sendto.sin_port = htons(CLI_PORT);
	si_sendto.sin_addr.s_addr = inet_addr(LHOST);

	return result = OP_SUCCESS;
}

int skb2u_open()
{
	int result = OP_FAILURE;
	int slen = sizeof(si_b2u);

    skb2u.sid_b2u = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(skb2u.sid_b2u < 0)
    {
        debug_log("skb: open error");
		//set_system_state(LHOST, SOCK_ERR);
        return result;
    } 

	memset ((char *) &si_b2u, 0, slen);

	si_b2u.sin_family = AF_INET;
	si_b2u.sin_port = htons(SRV_PORT);
	#if 1
		si_b2u.sin_addr.s_addr = inet_addr(LHOST);
	#else
		si_b2u.sin_addr.s_addr = htonl(INADDR_ANY);
	#endif

	if(bind(skb2u.sid_b2u, (struct sockaddr *)&si_b2u, sizeof(si_b2u)) < 0)
	{
        debug_log("skb: bind error");
		//set_system_state(LHOST, SOCK_ERR);
        return result;
	}

#if 1
	result = init_cli_send();
	if (result == OP_FAILURE)
	{
		return result;
	}
#endif
	debug_log("skb: init success ...\n");

	return result = OP_SUCCESS;
}

int skb2u_send()
{
	int slen = sizeof(si_sendto);

	if(sendto(skb2u.sid_b2u, skb2u.send_buf, skb2u.send_len, 0, 
		(struct sockaddr *)&si_sendto, slen) < 0)
	{
 		debug_log("skb: send error");
	}
}

int skb2u_recv()
{
	int slen = sizeof(si_sendto);

	if(skb2u.recv_len = recvfrom(skb2u.sid_b2u, skb2u.recv_buf, RECV_LEN, 0, 
		(struct sockaddr *)&si_sendto, &slen) < 0)
	{
		debug_log("skb: recv error");
		
	}
	debug_log("recv packet from %s:%d", 	
	inet_ntoa(si_sendto.sin_addr), ntohs(si_sendto.sin_port));
	debug_log("skb: recv data: %s\n", skb2u.recv_buf); 
}

#if 0
int main(void)
{
    int result = OP_FAILURE;
	int slen = sizeof(si_other);
    //getaddrinfo

    skb2u = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(skb2u < 0)
    {
        debug_log("socket open error");
        return result;
    } 
	debug_log("socket open success");

	memset ((char *) &si_b2u, 0, sizeof(si_b2u));

	si_b2u.sin_family = AF_INET;
	si_b2u.sin_port = htons(SRV_PORT);
	si_b2u.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(skb2u, (struct sockaddr *)&si_b2u, sizeof(si_b2u)) < 0)
	{
        debug_log("bind error");
	}
	debug_log("socket bind success");
	
	while(1)
	{
		if(recv_len = recvfrom(skb2u, recv_buf, RECV_LEN, 0, 
			(struct sockaddr *)&si_other, &slen) < 0)
		{
            debug_log("recv error");
			
		}
	    debug_log("recv packet from %s:%d", 	
		inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	    debug_log("recv data: %s\n", recv_buf); 

	}
	
	if(sendto(skb2u, skb2u_buf, send_len, 0, 
		(struct sockaddr *)&si_other, slen) < 0)
	{
 		debug_log("send error");
	}
	

}
#endif
