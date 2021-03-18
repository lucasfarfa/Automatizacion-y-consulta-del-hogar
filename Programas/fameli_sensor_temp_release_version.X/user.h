/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de user
 * 
 * Aquí se definen macros, tipos de datos y se declaran las funciones y datos 
 * externos de user
 */
#ifndef USER_H
#define USER_H
/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/
/* User Level #define Macros                                                 */
/* TODO: Los parámetros de user.c pueden ponerse aquí */

#define	TRIS_RE    TRISAbits.TRISA2
#define	PIN_RE       PORTAbits.RA2

#define	TRIS_DE    TRISAbits.TRISA1
#define	PIN_DE       PORTAbits.RA1

#define	TRIS_LED     TRISBbits.TRISB0
#define	PIN_LED       PORTBbits.RB0



#define	BAUDRATE        9600

#define TEMP_ADDR 0x95
#define HUM_ADDR 0x96

typedef enum {UART_TX,UART_RX,MEASURING,IDDLE} estadoTemp_t;

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/
//extern char datoUser; //Ejemplo
/*==================[tipos de datos declarados por el usuario]===============*/
typedef uint16_t tick_t; // Define tipo de dato para Tick 

/*==================[declaraciones de datos externos]========================*/
//extern char datoUser; //Ejemplo
extern volatile tick_t tickCounter; //Contador de Tick
extern volatile uint8_t intC;
/*==================[declaraciones de funciones externas]====================*/
/* TODO: Los prototipos de User level (ej. InitApp) van aquí */
void initApp(void);     /* Inicializa las I/O y los periféricos */
void uartConfig(void);  /* Inicialización de UART */
void uartWriteByte( uint8_t value );        /* Envia un byte en forma boqueante */
bit uartReadByte( uint8_t* receivedByte );
void putch(char data);  /* Pone un byte en stdout */
char getch(void);       /* Toma un byte en stdin  */
char getche(void);      /* Toma un byte en stdin con eco */
tick_t tickRead( void );        /* Lee Tick Counter */
void tickWrite( tick_t ticks ); /* Escribe Tick Counter */
void TxMode(void);
void RxMode(void);
void IniciarMEFtemp(void);
void ActualizarMEFtemp(void);
bit ReadTemp(uint8_t* data);



/*==================[fin del archivo]========================================*/
#endif// USER_H
