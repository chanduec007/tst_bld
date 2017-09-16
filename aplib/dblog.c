
/*
 * PROJECT NAME: Application Framework
 * Platform: BB
 * @file: dblog.c
 * @brief: 
 * Function: debug log module
 * Created on:
 * Revision-Date: 0.1 - 27/June/2017
 * Author: FGT
 */

#include "os_includes.h"
#include "dblog.h"

char temp_buf[512];

void debug_log(const char *string, ...)
{
	int log_to;
	va_list dlist;

	va_start(dlist, string);
	(void)vsnprintf(temp_buf, sizeof(temp_buf), string, dlist);
	va_end(dlist);

	log_to = D2SCRN;


	/* first append current TS to string */

	if (log_to == D2SCRN)
	{
		printf("d2scr: %s \n", temp_buf);
	} else if (log_to == D2FILE)
	{
	} else
	{
	}


}











