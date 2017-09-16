/***************************************
            HEADER FILES
***************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/fs.h>
#include <unistd.h>
#include <fcntl.h>

#include "i2c-dev.h"
#include "i2c.h"

/**********************************************
		 MAIN 
**********************************************/
int main (int argc, char *argv[])
{

	struct i2c_descriptor_t i2c_desc;
	i2c_desc.i2c_dev = "/dev/i2c-1";
	i2c_desc.REG_ADDR = 0x07;
	i2c_desc.addr = 0x68;

	if (argc < 2) {
		printf("\n Usage : ./i2c-check <value> \
			\n Try : ./i2c-check 0x2f \n \n");
		return 0;
	}

	i2c_desc.REG_VAL = i2c_htoi(argv[1]);

	printf("\n *** I2C DEVICE TESTING *** \n");

	i2c_desc.res = i2c_fd_open(&i2c_desc);


	if (i2c_desc.res < 0) {
		printf("error in open\n");
		return -1;
	}

	i2c_desc.res = i2c_write_data(&i2c_desc);
	if (i2c_desc.res < 0) {
		printf("error in write\n");
		return -1;
	}

	i2c_desc.res = i2c_read_data(&i2c_desc);
	if (i2c_desc.res < 0) {
		printf("error in read\n");
		return -1;
	}

	printf("\n Dev-Addr = %.2x | Reg-Addr = %.2x | Reg-Val = %.2x \n", i2c_desc.addr, i2c_desc.REG_ADDR, i2c_desc.res);

	close(i2c_desc.i2c_fd);
	return 0;
}



