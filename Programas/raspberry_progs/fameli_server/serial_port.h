#include <stdio.h>
#include <stdint.h>
//#include "UART.h"
#include <unistd.h>
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <string.h> //para usar strlen
#include <stdlib.h>


static int uart0_filestream;

void uartConfig(void);
int open_uart(void);
int close_uart(void);
int uartReadByte(uint8_t* data);
int uartWriteByte(uint8_t data);
