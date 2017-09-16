/*
 * PROJECT NAME: Application Framework
 * Platform: BB
 * @file: main.c
 * @brief: 
 * Function: Main Application Module 
 * Created on:
 * Revision-Date: 0.1 - 11/June/2017
 * Author: FGT
 */

#include "os_includes.h"
#include "hal_includes.h"
#include "appmn.h"
#include "cserv.h"


/*
 * globals 
*/
uint32_t handle_exception()
{
	while(1)
	{
		//blink red led
		//log exception
		//try reset
	}
}

uint32_t application_init()
{
	skb2u_open();

}
 
int main(void)
{	
	msd01_t msd01;
	uint32_t result, len = 0;

    platform_init();
	/*
	if (error)
	{
		handle_exception();
	}
	*/

	debug_log("platform init done ...\n");

	application_init();
	/*
	if (error)
	{
		handle_exception();
	}
	*/
	debug_log("application init done ...\n");

#if 1 /* test modules */
	len = prepare_jmsd01(msd01);
#endif /* test modules */

#if 1	
	while(1)
	{
		printf("sml ...\n");
		skb2u_send();
		sleep(2);
		skb2u_recv();
	
	}	
#endif

	return 1;
}

