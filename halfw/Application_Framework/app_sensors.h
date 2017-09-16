/**************************************************
 * PROJECT NAME: HMI Application Framework

 * Platform: BBB

 * @file: app_sensors.h

 * Function: Sensors module header APIs

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***************************************************/

#ifndef SENSORS_MODULE_H
#define SENSORS_MODULE_H

/************************************************** 
	ADXL345 Accelerometer Sensor 
***************************************************/
#define ADXL_ADDRESS	0x53
#define	DEVID		0x00
#define POWER_CTL	0x2D
#define DATAX0		0x32
#define DATAX1		0x33
#define DATAY0		0x34
#define DATAY1		0x35
#define DATAZ0		0x36
#define DATAZ1		0x37

int board_init(void);     
int adxl_init(void);  

/************************************************** 
	L3GD20H Gyroscope Sensor 
***************************************************/
#define L3GD20H_ADDRESS	0x6a
#define WHO_AM_I	0x0F
#define CTRL_REG1	0x20
#define CTRL_REG2	0x21
#define CTRL_REG3	0x22
#define	CTRL_REG4	0x23
#define CTRL_REG5	0x24
#define OUT_X_L		0x28
#define OUT_X_H     	0x29
#define OUT_Y_L		0x2A
#define OUT_Y_H		0x2B
#define OUT_Z_L		0x2C
#define OUT_Z_H		0x2D

int l3gd20h_init(void); 


#endif
