/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene la rutina de interrupción
 * 
 * Aqui se encuentra la implementación de la rutina de interrupción
 */
/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "usb_config.h"
#include "usb_device.h"
#include "usb_device_cdc.h"



/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
void interrupt isr(void);

/*==================[definiciones de funciones internas]=====================*/
/**
 * @brief	Rutina de interrupción
 * @return	Nada
 * @note    Completar con codigo de interrupción necesario
 */

void interrupt isr(void) {
    /* El sig. ejemplo de codigo muestra el manejo de interrupciones.
    Note que no son bloques if separados sino que son if else ecadenados.
    No use bloques if separados para cada flag de interrupción para evitar
    errores en tiempo de ejecución. */
    /* TODO: Complete con el codigo de las rutinas de interrupción aquí. */
    /* Determine que flag ha generado la interrupción */
    if(TMR0IF) {

      TMR0IF = 0; /* Baja Interrupt Flag 1 */
      TMR0 += 7;
      tickCounter++;

    
    }
    else{
        USBDeviceTasks();
    }
    //else if(TMR2IF) {
    //  TMR2IF=0; /* Baja Interrupt Flag 2 */
    //  ...
    //}
    //else {
    //  /* Interrupción de tipo inesperado */
    //}
}

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/