#ifndef _I2C_H
#define _I2C_H

struct i2c_descriptor_t {
	char *i2c_dev;
	int i2c_fd;
	int addr;
	int res;
	int REG_ADDR;
	int REG_VAL;
};

/* Below Functions are used in I2C - Library/Test Program */
int i2c_fd_open(struct i2c_descriptor_t *);
int i2c_write_data(struct i2c_descriptor_t *);
int i2c_read_data(struct i2c_descriptor_t *);
int i2c_fd_close(struct i2c_descriptor_t *);
int i2c_htoi(char *); 

#endif
