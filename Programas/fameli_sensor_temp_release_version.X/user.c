/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de user
 * 
 * Aquí se encuentra la implementación de users, los defines, macros, 
 * datos internos y externos, declaraciones y definiciones de funciones
 * internas y definiciones de funciones externas.
 */

/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

#include "system.h"     /* Funciones/Parametros System, como conf de osc/perif */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "DHT11.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
//char datoUser; //Ejemplo
volatile tick_t tickCounter;/* This global variable holds the tick count */
static estadoTemp_t estadoActualTemp;
static tick_t tinicio;
/*==================[declaraciones de funciones internas]====================*/
//static void funcUser(void); //Ejemplo

/*==================[definiciones de funciones internas]=====================*/
//static void funcUser(void){ //Ejemplo
//}; 

/*==================[definiciones de funciones externas]=====================*/
/**
 * @brief	Inicializa Ports, Periféricos e Interrupciones
 * @return	Nada
 */
void initApp(void) {
    /* TODO: Inicializar Ports/Periféricos/Interrupciones */

    /* Configura funciones analógicas y dirección de los Ports de I/O */
    CM2=1;
    CM1=1;
    CM0=1;//todo digital
    
   
    TRIS_LED = 0;
    TRIS_DE = 0;
    TRIS_RE = 0;
    RxMode();
   uartConfig();
   
    __delay_ms(100); //Espera que se estabilice la fuente
    T0CS = 0;       //Internal instruction cycle clock (FOSC/4)
    PSA = 0;        //Prescaler Assignment bit
                    // 1 = Prescaler is assigned to the WDT
                    // 0 = Prescaler is assigned to the Timer0 module
    PS0=1;  //PS<2:0>: Prescaler Rate Select bits
    PS1=0;
    PS2=0;                /* 1 : 2 
                            * 1 : 4 
                             * 1 : 8
                             * 1 : 16<-
                             * 1 : 32
                             * 1 : 64
                             * 1 : 128
                             * 1 : 256 */

    //PEIE = 1;
    T2CON=0;

    TMR0IE=1;
    GIE = 1;
    
    
    /* TODO: Habilita Interrupciones si es necesario*/
    //TMR2IE = 1;
    //PEIE = 1;
    //GIE = 1;  
}

/**
 * @brief	Configura e inicializa la UART
 * @return	Nada
 * @note    Las opciones se modifican en el código, por ejemplo con la 
 * constante BAUDRATE
 * @sa      BAUDRATE    
 */

void putch(char data) {
    while (!TXIF)   //Espera que haya espacio en la FIFO (bloquea poco tiempo)
        continue;
    TXREG = data;   //Envía el byte
}

/**
 * @brief       Envía un byte en forma bloqueante pero por poco tiempo
 * @param[in]   value Valor a transmitir 
 * @return      Nada
 */
void uartWriteByte( uint8_t value ){
    while (!TXIF)   //Espera que haya espacio en la FIFO (bloquea poco tiempo)
        continue;
    TXREG = value;  //Envía el byte
}

/**
 * @brief	Toma un byte de la entrada stdin en forma bloqueante
 * @return	El byte recibido
 * @note    Define la entrada estandar para la librería stdio
 */
char getch(void) {
    while (!RCIF)   //Espera hasta que haya un byte recibido (bloqueante)
        continue;
    return RCREG;   //retorna lo recibido
}

/**
 * @brief       Toma un byte de la FIFO de recepción en forma no bloqueante, chequea primero si hay un dato disponible
 * @param[out]  receivedByte Apunta al destino para el byte recibido
 * @return      1 si hay un byte recibido, 0 si no hay dato disponible 
 */
bit uartReadByte( uint8_t* receivedByte ){
   if ( RCIF ){     //Si hay por lo menos un byte recibido
      *receivedByte = RCREG;    //lo coloca en el lugar de destino
      return 1;     //Retorna 1 para indicar que há recibido
   }
   return 0;        //Retorna 0 para indicar que no há recibido
}

/**
 * @brief	Toma un byte de la entrada stdin con eco y en forma bloqueante
 * @return  El byte recibido
 * @note
 */
char getche(void) {
    char data;
    while (!RCIF)   //Espera hasta que haya un byte recibido (bloqueante)
        continue;
    data = RCREG;   //almacena lo recibido
    while (!TXIF)   //Espera que haya espacio en la FIFO (bloqueante poco tiempo)
        continue;
    TXREG = data;   //Envía el byte
    return data;    //retorna lo recibido
}

tick_t tickRead( void ) {
    tick_t aux;
    GIE = 0;                        //Inicia Zona critica
    aux = tickCounter;              //  Operaciones atomicas
    GIE = 1;                        //Finaliza la zona critica
    return aux;
}

/* Escribe Tick Counter */
void tickWrite( tick_t ticks ) {
    GIE = 0;                        //Inicia Zona critica
    tickCounter = ticks;            //  Operaciones atomicas
    GIE = 1;                        //Finaliza la zona critica
}

void uartConfig(void) {
#if((SYS_FREQ - BAUDRATE*16L)/(BAUDRATE*16L)) > 255 //Si necesita High Baud Rate
#if	(SYS_FREQ - BAUDRATE*64L)/(BAUDRATE*64L) > 255
#error Baud Rate demasiado Bajo
#endif
    SPBRG = (SYS_FREQ - BAUDRATE * 64L) / (BAUDRATE * 64L); //SPBRG para Low Baud Rate
    BRGH = 0;   //Selecciona Low Baud Rate
#else
    SPBRG = (SYS_FREQ - BAUDRATE * 16L) / (BAUDRATE * 16L); //SPBRG para High Baud Rate
    BRGH = 1;   //Selecciona High Baud Rate
#endif
    SYNC = 0;   //Selecciona Modo Asincronico
    SPEN = 1;   //Habilita Serial Port
    TRISB2=0;
    TRISB1=1;
    CREN = 1;   //Habilita Continuous Reception
    TXEN = 1;   //Habilita Transmision
}

void TxMode(void){
    PIN_RE=0;
    PIN_DE=1;
    
}
void RxMode(void){
    PIN_RE=0;
    PIN_DE=0;
}

bit ReadTemp(uint8_t* data) {
    uint8_t i;
    if (DHT11StartSignal()) {
        if (DHT11CheckResponse()) {

            GIE = 0;
            for (i = 0; i < 5; i++) {
                DHT11ReadByte(&data[4 - i]);
            }
            GIE = 1;
            return 1;
        }
        else return 0;
    }
    else return 0;
}

void IniciarMEFtemp(void){
    estadoActualTemp=MEASURING;
    tinicio=tickRead();
}
void ActualizarMEFtemp(void){
    static uint8_t i,res;
    static uint8_t temp,data[5],hum,aux;
    switch (estadoActualTemp) {
        case IDDLE:
            if(tickRead()-tinicio>5000){
                estadoActualTemp=MEASURING;
                tinicio=tickRead();
            }
            else{
                estadoActualTemp=UART_RX;
            }
            break;
        case UART_RX:
            RxMode();
            if (uartReadByte(&res)) {
                if (res == TEMP_ADDR) {
                    aux=TEMP_ADDR;
                    res = 0;
                    estadoActualTemp = UART_TX;
                }
                else if(res == HUM_ADDR){
                    res=0;
                    aux=HUM_ADDR;
                    estadoActualTemp = UART_TX;
                    
                }
            }
            else{
                estadoActualTemp=IDDLE;
            }
            break;

        case UART_TX:
            if (aux == TEMP_ADDR) {
                TxMode();

                uartWriteByte(temp);
                while (!uartReadByte(&res));
                if (res == temp) {
                    RxMode();
                    estadoActualTemp = IDDLE;
                } else {
                    estadoActualTemp = UART_TX;
                }
            } else if(aux==HUM_ADDR){
                TxMode();
                uartWriteByte(hum);
                while (!uartReadByte(&res));
                if (res == hum) {
                    RxMode();
                    estadoActualTemp = IDDLE;
                } else {
                    estadoActualTemp = UART_TX;
                }
            }
    
    
    break;
        case MEASURING:
            SPEN=0;
            CREN=0;
            if(ReadTemp(data)){
              temp=data[2];
              hum=data[0];
              SPEN=1;
              CREN=1;
              estadoActualTemp=IDDLE;
            }
            break;          
    }
}


/**
 * @brief	Envia un byte en la salida stdout
 * @param	data Byte o dato a transmitir
 * @return	Nada
 * @note    Define la salida estandar para la librería stdio
 */




/*==================[fin del archivo]========================================*/
