
#include "../common/os_includes.h"
#include "../common/hal_includes.h"

int platform_init(void)
{	
#if 0
	i2c_init(i2c1);
	i2c1_fd = i2c_init(i2c1);
	adxl_init();
	l3gd20h_init();
	uart_init();	
#endif //#if 0
	printf("Board Initialization is Completed.\n");
}
