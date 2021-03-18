#include <stdio.h>
//#include "UART.h"
#include <unistd.h>
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <string.h> //para usar strlen
#include <stdlib.h>
#include <stdint.h>
#include "serial_port.h"


static int uart0_filestream=-1;

void uartConfig(void){
    struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
}

int open_uart(void){
char path[50];
FILE *arch;
arch = fopen("uart.ini","r");
if(arch==NULL){
    printf("Error en abrir uart.ini \n");
    return -1;
}
fscanf(arch,"%[^\n]",path);
fclose(arch);
uart0_filestream = open(path, O_RDWR | O_NOCTTY | O_NDELAY);
return uart0_filestream;
}


int close_uart(void){
return close(uart0_filestream);
}

int uartReadByte(uint8_t* data){
return read(uart0_filestream,data,1);
}

int uartWriteByte(uint8_t data){
return write(uart0_filestream,&data,sizeof(data));
}

