/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de teclado
 * 
 * Aqui se encuentra la implementación de teclado, los defines, macros, 
 * datos internos y externos, declaraciones y definiciones de funciones
 * internas y definiciones de funciones externas
 */

/*==================[inclusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

#include "system.h"     /* Funciones/Parametros System, como conf de osc/perif */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "teclado.h"    /* Funciones/Parametros del Teclado */

/*==================[definiciones y macros]==================================*/
// Nuevo tipo de datos enumerado llamado estadoMEF
typedef enum{
            INICIASCAN, 
            ELIGE_F1, 
            LEECOLS_F1, 
            ELIGE_F2, 
            LEECOLS_F2, 
            ELIGE_F3, 
            LEECOLS_F3, 
            ELIGE_F4, 
            LEECOLS_F4
} estadoMEF_t;// Nuevo tipo de datos enumerado llamado estadoMEF
//typedef enum{
//            TEC_SUELTAS, 
//            TEC_BAJANDO, 
//            TEC_PRESIONADA, 
//            TEC_SUBIENDO 
//} estadoMEFTec_t;// Nuevo tipo de datos enumerado llamado estadoMEFTec

/*==================[definiciones de datos internos]=========================*/
uint8_t scanCode;
bit hayTecla = 0;

/*==================[definiciones de datos externos]=========================*/
//char datoUser; //Ejemplo
/* This global variable holds the tick count */


/*==================[declaraciones de funciones internas]====================*/
//static void funcUser(void); //Ejemplo

/*==================[definiciones de funciones internas]=====================*/
//static void funcUser(void){ //Ejemplo
//}; 

/*==================[definiciones de funciones externas]=====================*/
/**
 * @brief	Configura e inicializa el teclado y actualiza su MEF 
 * @return	Nada
 * @note    Se debe debe llamar periodicamente 
 */
void ActualizarMEFTeclado(void){
    static estadoMEF_t  estadoActual = INICIASCAN;  // Variable de estado (global) y Establece estado inicial ;
//  static estadoMEFTec_t  estadoActualTec = TEC_SUELTAS; // Variable de estado (global) y Establece estado inicial ;   
    static uint8_t scanCodeAux, scanCodeTemp, tAntiRebote;
    
	switch (estadoActual) {
		case INICIASCAN:
            //Configura todas las filas como entradas
            TRIS_TEC_F1 = 1;    
            // ...
            //Configura todas las columnas como entradas
            TRIS_TEC_C1 = 1;    
            // ...
            //Pone todas las salidas en cero para las filas para trabajar con pullups
            PIN_TEC_F1 = 0;     
            // ...
            estadoActual = ELIGE_F1;        // Establece estado prox
            break;
		case ELIGE_F1:
            scanCodeAux = 0;
            // ...                          // Setea como salida en 0
                                            // Las demas en entrada
            
                                            // Establece estado prox
            break;
        case LEECOLS_F1:
            if(PIN_TEC_C1 == 0) scanCodeAux = 1; 
            // ...
             
                                            // Establece estado prox           
            break;
        case ELIGE_F2:
            // ...                          // Setea como salida en 0
                                            // Las demas en entrada     
            
                                            // Establece estado prox
            break;
        case LEECOLS_F2:
            // ...

            
                                            // Establece estado prox
            break;
        case ELIGE_F3:
            // ...                          // Setea como salida en 0
                                            // Las demas en entrada            
            
                                            // Establece estado prox
            break;
        case LEECOLS_F3:
            // ...

            
                                            // Establece estado prox 
            break;
        case ELIGE_F4:
            // ...                          // Setea como salida en 0
                                            // Las demas en entrada            
            
                                            // Establece estado prox 
            break;            
        case LEECOLS_F4:
            // ...
            
            scanCode = scanCodeAux;      
            
                                            // Establece estado prox 
            break;
        default:
			//Si algo modificó la variable estadoActual 
			// a un estado no válido llevo la MEF a un 
			// lugar seguro, por ejemplo, la reinicio:
			//InicializarMEF();
            estadoActual = ELIGE_F1;  // Variable de estado (global) y Establece estado inicial ;       
	}
}
/**
 * @brief       Toma el codigo de una tecla presionada, chequea primero si hay tecla disponible
 * @param[out]  valorTecla Apunta al destino para la tecla presionada
 * @return      1 si hay una tecla disponible, 0 si no hay tecla disponible 
 */
//bit tecladoReadByte(uint8_t* valorTecla) {
//    const uint8_t tablaCodigos[] = { '\0',
//        '7', '8', '9', 'A',
//        '4', '5', '6', 'B',
//        '1', '2', '3', 'C',
//        '*', '0', '#', 'D',
//    };
//    if (hayTecla) {
//        *valorTecla = tablaCodigos[scanCode];
//        hayTecla = 0;
//        return 1;
//    }
//    return 0;
//}

/*==================[fin del archivo]========================================*/
