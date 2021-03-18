/*
 * File:   user.c
 * Author: FAMELI Tech
 *
 * Created on 18 de septiembre de 2019, 16:16
 */
#include <xc.h>         
#include <stdint.h>     
#include "system.h"     
#include "user.h" 
#include "i2c.h"

//VARIABLES GLOBALES
volatile tick_t tickCounter;
uint16_t result=0;


static estadoMEFI2C_t  estadoActualI2C; // Variable de estado (global)
static estadoMEFUART_t estadoActualUART;

tick_t tInicio,tActual; 
//DEFINICION DE FUNCIONES

void initApp(void) {
    CM2=1;
    CM1=0;
    CM0=0;
            
    ANSEL=0x00;
    TRIS_TEC1 = 1;
    TRIS_TEC2 = 1;
    TRIS_LED1 = 0;
    TRIS_LED2 = 0;
    TRIS_RE=0;
    TRIS_DE=0;
    
    uartConfig();
    
    //Configura Timer0
    T0CS = 0;       //Internal instruction cycle clock (FOSC/4)
    PSA = 0;        //Prescaler Assignment bit
                    // 1 = Prescaler is assigned to the WDT
                    // 0 = Prescaler is assigned to the Timer0 module
    OPTION_REGbits.PS = 1;  //PS<2:0>: Prescaler Rate Select bits
                            /* 1 : 2
                             * 1 : 4 <-
                             * 1 : 8
                             * 1 : 16
                             * 1 : 32
                             * 1 : 64
                             * 1 : 128
                             * 1 : 256 */
    
    __delay_ms(100);
    TMR0IE=1;
    GIE=1;
}





void uartConfig(void) {
#if((SYS_FREQ - BAUDRATE*16L)/(BAUDRATE*16L)) > 255 //Si necesita High Baud Rate
#if	(SYS_FREQ - BAUDRATE*64L)/(BAUDRATE*64L) > 255
#error Baud Rate demasiado Bajo
#endif
    SPBRG = (SYS_FREQ - BAUDRATE * 64L) / (BAUDRATE * 64L); //SPBRG para Low Baud Rate
    BRGH = 0; //Selecciona Low Baud Rate
#else
    SPBRG = (SYS_FREQ - BAUDRATE * 16L) / (BAUDRATE * 16L); //SPBRG para High Baud Rate
    BRGH = 1; //Selecciona High Baud Rate
#endif
    SYNC = 0; //Selecciona Modo Asincronico

    CREN = 1; //Habilita Recepción continua
    TXEN = 1; //Habilita Transmisión
    SPEN = 1; //Habilita Puerto Serie
    TRISB5=1;
    TRISB2=1;
}

bit uartReadByte(uint8_t* receivedByte) {
    if (RCIF) {
        *receivedByte = RCREG;
        return 1;
    }
    return 0;
}

void uartWriteByte(uint8_t value) {
    while (!TXIF)
        continue;
    TXREG = value;
}


void TxMode(void){
    PIN_RE=0;
    PIN_DE=1;
    
}
void RxMode(void){
    PIN_RE=0;
    PIN_DE=0;
}

tick_t tickRead( void ) {
    tick_t aux;
    GIE = 0;                        //Inicia Zona critica
    aux = tickCounter;              //  Operaciones atomicas
    GIE = 1;                        //Finaliza la zona critica
    return aux;
}

void tickWrite( tick_t ticks ) {
    GIE = 0;                        //Inicia Zona critica
    tickCounter = ticks;            //  Operaciones atomicas
    GIE = 1;                        //Finaliza la zona critica
}


void ActualizarMEFI2C(void) {
    static tick_t tinicioi2c;

    switch (estadoActualI2C) {
        case REQUEST:
            I2C_Start();
            I2C_WriteToAddress(I2C_ADDR_L);
            I2C_WriteByte(0b00010001);
            estadoActualI2C = WAIT;
            tinicioi2c = tickRead();
            break;
        case WAIT:
            if (tickRead() - tinicioi2c > 180) {
                estadoActualI2C = REPLY;
            }
            break;
        case REPLY:
            result = 0;
            I2C_Start();
            I2C_ReadFromAddress(I2C_ADDR_L);
            result = My_I2C_ReadResult();
            result <<= 8;
//             FALTA PULSO DE CLOCK ACK
            I2C_SendZero();
            result += My_I2C_ReadResult();
            I2C_SendOne();
            I2C_Stop();
            if(result&0x0080){
                result&=0xFF7F;
                result|=0x4000;
            }
            estadoActualI2C = REQUEST;           
    }
}

void InicializarMEFI2C(void){
    estadoActualI2C = REQUEST;
}

void InicializarMEFUART(void){
    estadoActualUART=RX;
}

void ActualizarMEFUART(void){
    static uint8_t res;
    uint8_t aux;
    uint16_t tout=0;
    tick_t tinicioUART;
    switch(estadoActualUART) {
        case RX:
            if(OERR==1){
                CREN=0;
                CREN=1;
            }
            RxMode();
            if (uartReadByte(&res)) {
                if (res == LUX_ADDR) {
                    res = 0;
                    estadoActualUART = TX;
                }
            }
            break;
        case TX:
            tout=0;
            tinicioUART=tickRead();
             PIN_LED2 = !PIN_LED2;
             PIN_LED1 = !PIN_LED1;
                TxMode();
                
                uartWriteByte((uint8_t)(result>>8));
                while(!(uartReadByte(&aux))&&(tout<0xFFFE)){
                    tout++;
                }
                if(aux == (uint8_t)(result >> 8)){
                   uartWriteByte((uint8_t)(result & 0x00FF));
                   tout=0;
                while(!(uartReadByte(&aux))&&(tout<0xFFFE)){
                    tout++;
                }
                if (aux == (uint8_t)(result & 0x00FF)) {
                    RxMode();
                    estadoActualUART = RX;
                }
                else {
                    RxMode();
                    estadoActualUART=RX;
                }
                }else{
                    RxMode();
                    estadoActualUART=RX;
                }
                

//                while(TRMT||!TXIF);


             break;
    }
}

