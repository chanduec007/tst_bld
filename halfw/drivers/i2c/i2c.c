/***************************************
	    HEADER FILES
***************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/fs.h>
#include <sys/ioctl.h>

#include "i2c-dev.h"
#include "i2c.h"

/* I2C - OPEN(fd) */
int i2c_fd_open(struct i2c_descriptor_t *i2c_desc)	
{
	int fd, addr, res;
	i2c_desc->i2c_fd = open(i2c_desc->i2c_dev, O_RDWR);
	if(i2c_desc->i2c_fd < 0)
		return i2c_desc->i2c_fd;
		
	// Set Device Address
	fd = i2c_desc->i2c_fd;
	addr = i2c_desc->addr;
	res = ioctl(fd, I2C_SLAVE, addr);

	return res;
}

/* I2C - WRITE DATA*/
int i2c_write_data(struct i2c_descriptor_t *i2c_desc)
{
	int fd, reg_addr, reg_val, res;

	fd = i2c_desc->i2c_fd;
	reg_addr = i2c_desc->REG_ADDR;
	reg_val = i2c_desc->REG_VAL;
	res = i2c_smbus_write_byte_data(fd, reg_addr, reg_val);

	if (res < 0) {
		close(i2c_desc->i2c_fd);
		return res;
	}

	return 0;
}

/* I2C - READ DATA */
int i2c_read_data(struct i2c_descriptor_t *i2c_desc)
{
	int fd, res,reg_addr;

	fd = i2c_desc->i2c_fd;
	reg_addr = i2c_desc->REG_ADDR;
	res = i2c_smbus_read_byte_data(fd,reg_addr);

	if (res < 0) {
		close(i2c_desc->i2c_fd);
	}

	return res;
}

/* I2C - HEX-TO-INTEGER */
int i2c_htoi (char *hexstr)
{
	char c;
	int val=0,i;
	int len=strlen(hexstr);

	for(i=0;i<len;i++) {
		c=*(hexstr+2);
		if(c>='a' && c<='f') {
			val=val*16+(c-'a'+10);
		}
		else if(c>='A' && c<='F') {
			val=val*16+(c-'A'+10);
		}
		else {
			if (c>='0' && c<='9') {
			val=val*16+(c-'0');
			}
		}
		hexstr++;
	}

	return val;
}

/* I2C - CLOSE(fd) */
int i2c_fd_close (struct i2c_descriptor_t *i2c_desc)
{
	close(&i2c_desc->i2c_fd);

	i2c_desc->i2c_fd = -1;
	return 0;
}

