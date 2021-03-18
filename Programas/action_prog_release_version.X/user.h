// CODIGO HECHO POR FAMELI
#ifndef USER_H
#define USER_H

#include <stdint.h>

//DIRECCIONES 
#define RELE1_ON_ADDR      0xC1             //ACTIVAR RELE 1 Y 2
#define RELE2_ON_ADDR      0xC2

#define RELE1_OFF_ADDR     0xC3             //APAGAR RELE 1 Y 2
#define RELE2_OFF_ADDR     0xC4

#define RELE1_ASK_ADDR     0xC6             //CONSULTA RELE 1 Y 2   
#define RELE2_ASK_ADDR     0xC7

#define OK     0xC8

#define ITS_ON  0x75
#define ITS_OFF 0x79


//MACROS
#define	TRIS_TEC1       TRISBbits.TRISB4
#define	PIN_TEC1        PORTBbits.RB4

#define	TRIS_TEC2       TRISBbits.TRISB5
#define	PIN_TEC2        PORTBbits.RB5

#define	TRIS_LED1       TRISBbits.TRISB0
#define	TRIS_LED2       TRISBbits.TRISB3

#define	PIN_LED1        PORTBbits.RB0
#define	PIN_LED2        PORTBbits.RB3

#define	TRIS_RELE1      TRISAbits.TRISA3
#define	PIN_RELE1       PORTAbits.RA3

#define	TRIS_RELE2      TRISAbits.TRISA4
#define	PIN_RELE2       PORTAbits.RA4

#define	TRIS_RE       TRISAbits.TRISA2
#define	PIN_RE        PORTAbits.RA2

#define	TRIS_DE       TRISAbits.TRISA1
#define	PIN_DE        PORTAbits.RA1

#define	BAUDRATE        9600

//DECLARACIONES DE FUNCIONES

typedef enum{RX,TX,ACTION} estadoMEFUART_t;

//DECLARACION DE DATOS 
typedef uint16_t tick_t;
extern volatile tick_t tickCounter; //Contador de Tick

//DECLARACIONES DE FUNCIONES
void initApp(void);
void uartConfig(void);
void uartWriteByte(uint8_t value);
bit uartReadByte(uint8_t* receivedByte);
void TxMode(void);
void RxMode(void);
void tickWrite(tick_t ticks);

tick_t tickRead(void);

#endif// USER_H
