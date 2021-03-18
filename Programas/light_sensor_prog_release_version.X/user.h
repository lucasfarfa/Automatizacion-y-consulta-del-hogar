/*
 * File:   user.h
 * Author: FAMELI Tech
 *
 * Created on 18 de septiembre de 2019, 16:16
 */
#ifndef USER_H
#define USER_H

#include <stdint.h>

#define I2C_ADDR_H    0b1011100
#define I2C_ADDR_L    0b0100011

#define LUX_ADDR      0xA8

//MACROS

#define	TRIS_RE       TRISAbits.TRISA2
#define	PIN_RE        PORTAbits.RA2

#define	TRIS_DE       TRISAbits.TRISA1
#define	PIN_DE        PORTAbits.RA1

#define	TRIS_LED1       TRISBbits.TRISB0
#define	PIN_LED1        PORTBbits.RB0

#define	TRIS_LED2       TRISBbits.TRISB3
#define	PIN_LED2        PORTBbits.RB3

#define TRIS_TEC1       TRISAbits.TRISA3
#define PIN_TEC1        PORTAbits.RA3

#define TRIS_TEC2       TRISAbits.TRISA4
#define PIN_TEC2        PORTAbits.RA4

#define	BAUDRATE        9600

typedef enum{REQUEST,WAIT,REPLY} estadoMEFI2C_t;
typedef enum{RX,TX,RX2,TX2} estadoMEFUART_t;
//DECLARACION DE DATOS 
typedef uint16_t tick_t;
extern volatile tick_t tickCounter; //Contador de Tick
//DECLARACIONES DE FUNCIONES
void InicializarMEFI2C(void);
void ActualizarMEFI2C(void);
void InicializarMEFUART(void);
void ActualizarMEFUART(void);
void initApp(void);
void uartConfig(void);
void uartWriteByte(uint8_t value);
bit uartReadByte(uint8_t* receivedByte);
void TxMode(void);
void RxMode(void);
void tickWrite(tick_t ticks);
tick_t tickRead(void);


#endif// USER_H
