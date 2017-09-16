/***********************************************************
 * PROJECT NAME: HMI Test Framework

 * Platform: BBB

 * @file: hal_uart.h

 * Function: GPIO Interface module header APIs

 * Created on:

 * Version: 0.1

 * Version date:

 * Author: Faregeo Technologies
***********************************************************/

#ifndef UART_MODULE_H
#define UART_MODULE_H

#define UART1	"/dev/ttyO1"
#define UART2	"/dev/ttyO2"

typedef enum {
		uart1 = 1,
		uart2}uart_t;

int board_init(void);
int uart_init(uart_t uart_port, int stop_bit, int data_bit, int *uart_handler);
void uart_handler(int status);


#endif
