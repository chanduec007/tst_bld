
#ifndef APP_MN_H
#define APP_MN_H

#include "dblog.h"
#include "jlibs.h"

typedef enum {
	DISPLAY_CHK,
	DISPLAY_KEYPAD_CHK,
	TOUCH_CHK,
	BACKLIGHT_CHK,
	AMBI_SENSOR_CHK,
	DATA_CARD_CHK,

	SERVER_COMM_CHK,
	

	MAX_CHK_MODULES
} idu_modules_t;
idu_modules_t idu_system_check[MAX_CHK_MODULES];

typedef enum
{
	NO_ERROR = 0,
	POSSIBLE_ERROR,
	OUT_OF_ORDER,

	SOCK_ERR
} module_states_t;


/*
 * global APIs
 */
void set_system_state(idu_modules_t module, module_states_t);
void get_system_state(idu_modules_t module);
void clear_system_state(void);



#endif
