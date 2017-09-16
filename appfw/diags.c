
#include "os_includes.h"
#include "appmn.h"


void set_system_state(idu_modules_t module, module_states_t state)
{
	if(module < MAX_CHK_MODULES)
	{
		idu_system_check[module] = state;
	}
	if (state != NO_ERROR)
	{
		debug_log("system state error: module:%d error:%d\n", module, state);
	}

}

void get_system_state(idu_modules_t module)
{

}

void clear_system_state(void)
{

}
