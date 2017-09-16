#ifndef CSERV_H
#define CSERV_H

typedef enum 
{
	ERROR,
	ONLINE,
	CLOSED
} sock_status_t;	

#define RECV_LEN 512
#define SEND_LEN 1024

//#define LHOST "127.0.0.1"
#define SRV_PORT 8888
#define CLI_PORT 45454


typedef struct
{
	int sid_b2u;
	sock_status_t status; //ONLINE, CLOSED, ERROR;
	uint32_t send_len;
	uint32_t recv_len;
	char send_buf[SEND_LEN];
	char recv_buf[RECV_LEN];
} skb2u_t;

skb2u_t skb2u;
int skb2u_open();
int skb2u_send();
int skb2u_recv();









#endif // CSERV_H
