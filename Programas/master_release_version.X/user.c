/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de user
 * 
 * Aqui se encuentra la implementación de users, los defines, macros, 
 * datos internos y externos, declaraciones y definiciones de funciones
 * internas y definiciones de funciones externas
 */

/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

#include "system.h"     /* Funciones/Parametros System, como conf de osc/perif */
#include "user.h"       /* Funciones/Parametros User, como InitApp */

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
//char datoUser; //Ejemplo
/* This global variable holds the tick count */
volatile tick_t tickCounter;/* This global variable holds the tick count */



//volatile tick_t tickRateMS;
//volatile sAPI_FuncPtr_t tickHookFunction = sAPI_NullFuncPtr;

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
    /* TODO: Inicializa Ports/Periféricos/Interrupciones */

    /* Configura funciones analógicas y dirección de los Ports */
    PCFG3=1;
    PCFG2=1;
    PCFG1=1;
    PCFG0=1; //todos los pines digitales.

    TRIS_TEC1 = 1;
    TRIS_TEC2 = 1;
    TRIS_TEC3 = 1;
    TRIS_TEC4 = 1;
    TRIS_DE=0;
    TRIS_RE=0;
    
    TRIS_LED1 = 0;
    TRIS_LED2 = 0;
    TRIS_LED3 = 0;
    TRIS_LED4 = 0;
    uartConfig();
    
    //Configura el TIMER0
    T0CS = 0;       //Internal instruction cycle clock (FOSC/4)
    PSA = 0;        //Prescaler Assignment bit
                    // 1 = Prescaler is assigned to the WDT
                    // 0 = Prescaler is assigned to the Timer0 module
    T0PS0=1;  //PS<2:0>: Prescaler Rate Select bits
    T0PS1=1;
    T0PS2=0;                /* 1 : 2 
                            * 1 : 4 <-
                             * 1 : 8
                             * 1 : 16
                             * 1 : 32
                             * 1 : 64
                             * 1 : 128
                             * 1 : 256 */
    
    //Configura el TIMER1
    TMR1CS = 0;     //Timer1 Clock Source Select bit: 0 = Internal clock (FOSC/4)
    T1CKPS0 = 0;    //T1CKPS<1:0>:Timer1 Input Clock Prescale Select bits
    T1CKPS1 = 0;    /* 11 = 1:8 Prescale Value
                     * 10 = 1:4 Prescale Value
                     * 01 = 1:2 Prescale Value
                     * 00 = 1:1 Prescale Value*/
    //TMR1ON = 1;     //Enables Timer1
    
    //Configura el modulo CCP1 como Comparador
	//CCP1CON = 0b00001011;	//Compare mode, trigger special event (CCPxIF bit is set; CCP1 resets TMR1)
    //CCPR1 = 1000;           //Compara con 1000 uSegs
    
  
    TMR0IE = 1;
    //PEIE = 1;
    GIE = 1;  
}

/**
 * @brief	Configura e inicializa la UART
 * @return	Nada
 * @note    Las opciones se modifican en el código, por ejemplo la 
 * constante BAUDRATE
 * @sa      BAUDRATE    
 */
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
    TRISC7 = 1;
    TRISC6 = 1;
    CREN = 1;   //Habilita Continuous Reception
    TXEN = 1;   //Habilita Transmision
}

/**
 * @brief	Envia un byte en la salida stdout
 * @param	data Byte o dato a transmitir
 * @return	Nada
 * @note    Define la salida estandar para la librería stdio
 */
void putch(char data) {
    while (!TXIF)
        continue;
    TXREG = data;
}

/**
 * @brief       Envia un byte en forma boqueante
 * @param[in]   value Valor a transmitir 
 * @return      Nada
 */
void uartWriteByte( uint8_t value ){
    // Wait for space in FIFO (blocking)
    while (!TXIF)
        continue;
    // Send byte
    TXREG = value;
}

/**
 * @brief	Toma un byte de la entrada stdin
 * @return	El byte recibido
 * @note    Define la entrada estandar para la librería stdio
 */
char getch(void) {
    while (!RCIF)
        continue;
    return RCREG;
}

/**
 * @brief       Toma un byte de la FIFO de recepción, chequea primero si hay un dato disponible
 * @param[out]  receivedByte Apunta al destino para el byte recibido
 * @return      1 si hay un byte recibido, 0 si no hay dato disponible 
 */
bit uartReadByte( uint8_t* receivedByte ){
   if ( RCIF ){
      *receivedByte = RCREG;
      return 1;
   }
   return 0;
}

/**
 * @brief	Toma un byte de la entrada stdin con eco
 * @return  El byte recibido
 * @note
 */
char getche(void) {
    char data;
    while (!RCIF)
        continue;
    data = RCREG;
    while (!TXIF)
        continue;
    TXREG = data;
    return data;
}

void displayWrite( uint8_t value ){
    const uint8_t tabla7seg[10] = {
        0b00111111, //0	
        0b00000110, //1	
        0b01011011, //2	
        0b01001111, //3	
        0b01100110, //4	
        0b01101101, //5	
        0b01111101, //6	
        0b00000111, //7	
        0b01111111, //8	
        0b01100111  //9	     
    };
   // PORTD = tabla7seg[value] ;  
}

/* Lee Tick Counter */
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
void TxMode(void){
    PIN_RE=0;
    PIN_DE=1;
    
}
void RxMode(void){
    PIN_RE=0;
    PIN_DE=0;
}



/*==================[fin del archivo]========================================*/
