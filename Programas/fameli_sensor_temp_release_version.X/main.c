/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene la funci�n principal
 * 
 * Aqu� se encuentra la implementaci�n de la funci�n principal
 */
/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* Para las definiciones de uint8_t por ej.*/
#include "system.h"     /* Funciones/Parametros System, como osc/peripheral config */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include <stdio.h>      /* Archivo de Encabezados StdIO */
#include "DHT11.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[funcion principal]======================================*/
void main(void) {
    /* TODO: Agregar el Cod1iogo de la Aplicaci�n aqu� */
   
    initApp();          /* Inicializa I/O y Perif�ricos de la aplicaci�n */
    IniciarMEFtemp();
    while(1){
        ActualizarMEFtemp();
    }

}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
