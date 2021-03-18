/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de user
 * 
 * Aqui se definen macros, tipos de datos y declaración de funciones y datos 
 * externos de user
 */
#ifndef USER_H
#define USER_H
/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/
/* User Level #define Macros                                                 */
/* TODO: Los parámetros de user.c pueden ponerse aqui */

////////////////////////////////// LEDS ///////////////////////////////////////

#define PIN_LED1        PORTAbits.RA3 /*ROJO*/
#define PIN_LED2        PORTAbits.RA2 /*AMARILLO*/
#define PIN_LED3        PORTAbits.RA1 /*VERDE*/
#define PIN_LED4        PORTAbits.RA0 /*AZUL*/

#define TRIS_LED1       TRISAbits.TRISA3
#define TRIS_LED2       TRISAbits.TRISA2
#define TRIS_LED3       TRISAbits.TRISA1
#define TRIS_LED4       TRISAbits.TRISA0

///////////////////////////////// TECLAS //////////////////////////////////////

#define	PIN_TEC1        PORTBbits.RB0
#define	PIN_TEC2        PORTBbits.RB1
#define	PIN_TEC3        PORTBbits.RB2
#define	PIN_TEC4        PORTBbits.RB3

#define	TRIS_TEC1       TRISBbits.TRISB0
#define	TRIS_TEC2       TRISBbits.TRISB1
#define	TRIS_TEC3       TRISBbits.TRISB2
#define	TRIS_TEC4       TRISBbits.TRISB3


#define	TRIS_RE    TRISCbits.TRISC0
#define	PIN_RE       PORTCbits.RC0

#define	TRIS_DE    TRISCbits.TRISC1
#define	PIN_DE       PORTCbits.RC1


///////////////////////////////// UART ///////////////////////////////////////

#define	TRIS_PICTX      TRISCbits.TRISC6
#define	PIN_PICTX       PORTCbits.RC6

#define	TRIS_PICRX      TRISCbits.TRISC7
#define	PIN_PICRX       PORTCbits.RC7

#define	BAUDRATE        9600
#define TRUE 1
#define FALSE  0

#define LUX_ADDR 0xA8
#define TEMP_ADDR   0x95
#define HUM_ADDR 0x96

#define RELE1_ON_ADDR   0xC1
#define RELE1_OFF_ADDR   0xC3
#define RELE2_ON_ADDR   0xC2
#define RELE2_OFF_ADDR   0xC4
#define RELE1_ASK_ADDR   0xC6
#define RELE2_ASK_ADDR   0xC7

#define OK  0xC8

#define ITS_ON  0x75
#define ITS_OFF 0x79


/*==================[tipos de datos declarados por el usuario]===============*/
typedef uint16_t tick_t; // Define tipo de dato para Tick 

/*==================[declaraciones de datos externos]========================*/
//extern char datoUser; //Ejemplo
extern volatile tick_t tickCounter; //Contador de Tick

/*==================[declaraciones de funciones externas]====================*/
/* TODO: Los prototipos de User level (ej. InitApp) van aqui */
void initApp(void);     /* Inicialización de I/O y eripheral Initialization */
void uartConfig(void);  /* Inicialización de UART */
void putch(char data);  /* pone un byte e stdout */
char getch(void);       /* toma un byte e stdin  */
char getche(void);      /* toma un byte e stdin con eco */
void uartWriteByte( uint8_t value );        /* Envia un byte en forma boqueante */
bit uartReadByte( uint8_t* receivedByte );  /* Toma un byte de la UART */
void displayWrite( uint8_t value );
void TxMode(void);
void RxMode(void);


tick_t tickRead( void );        /* Lee Tick Counter */
void tickWrite( tick_t ticks ); /* Escribe Tick Counter */
/*==================[fin del archivo]========================================*/
#endif// USER_H
