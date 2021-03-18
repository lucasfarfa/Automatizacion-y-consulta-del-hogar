/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones del sistema
 * 
 * Aquí se definen macros y bits de configuración del sistema
 */
#ifndef SYSTEM_H
#define SYSTEM_H
/*==================[inclusiones]============================================*/

/*==================[macros]=================================================*/
/* System Level #define Macros                                               */

/* TODO: Define system operating frequency */
/* Microcontroller MIPs (FCY) */
#define SYS_FREQ       4000000L
#define _XTAL_FREQ      SYS_FREQ
#define FCY             SYS_FREQ/4

/* Definición de Bits de Configuración */
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3/PGM pin io, low voltage programming disabled)
// CONFIG2


/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[fin del archivo]========================================*/
#endif// SYSTEM_H