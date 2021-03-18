/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene la rutina de interrupci�n
 * 
 * Aqu� se encuentra la implementaci�n de la rutina de interrupci�n
 */
/*==================[inlcusiones]============================================*/
#include <xc.h>             /* Archivo de Encabezados General XC8 */
#include "user.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
void interrupt isr(void);

/*==================[definiciones de funciones internas]=====================*/
/**
 * @brief	Rutina de interrupci�n
 * @return	Nada
 * @note    Completar con c�digo de interrupci�n necesario
 */
void interrupt isr(void) {
    /* El sig. ejemplo de c�digo muestra el manejo de interrupciones.
    Note que no son bloques if separados sino que son if else ecadenados.
    No use bloques if separados para cada flag de interrupci�n para evitar
    errores en tiempo de ejecuci�n. */
    /* TODO: Completar con el c�digo de las rutinas de interrupci�n aqu�. */
    /* Determina que flag ha generado la interrupci�n */

      if(TMR0IF){
      TMR0IF = 0; /* Baja Interrupt Flag 1 */
      TMR0 += 7;
      tickCounter++;
      }

 
    
    //else 
//    if(TMR2IF) {
//    TMR2IF=0; /* Baja Interrupt Flag 2 */
//    PIN_US=!PIN_US;
//    PIN_NUS=!PIN_NUS;
//    //}
//    //  ...
//    //}
//    //else {
//    //  /* Interrupci�n de tipo inesperado */
//    }
    

    
}
/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/



