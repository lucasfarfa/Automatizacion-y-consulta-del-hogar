// CODIGO HECHO POR FAMELI
#include <xc.h>         
#include <stdint.h>     
#include "system.h"     
#include "user.h"  

//VARIABLES GLOBALES
volatile tick_t tickCounter;

static estadoMEFUART_t estadoActual;
tick_t tInicio,tActual; 



void initApp(void) {
    CM2 = 1;
    CM1 = 1;
    CM0 = 1;
    
    TRIS_TEC1 = 1;
    TRIS_TEC2 = 1;
    TRIS_LED1 = 0;
    TRIS_LED2 = 0;
    TRIS_RELE1 = 0;
    TRIS_RELE2 = 0;
    TRIS_RE=0;
    TRIS_DE=0;
  
    PIN_LED1 = 0;
    PIN_LED2 = 0;
    
    uartConfig();

    __delay_ms(100);
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
    SPEN = 1; //Habilita Puerto Serie
    CREN = 1; //Habilita Recepción continua
    TXEN = 1; //Habilita Transmisión
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

tick_t tickRead(void) {
    tick_t aux;
    GIE = 0;
    aux = tickCounter;
    GIE = 1;
    return aux;
}

/* Escribe Tick Counter */
void tickWrite(tick_t ticks) {
    GIE = 0;
    tickCounter = ticks;
    GIE = 1;
}

void InicializarMEF(void){
    estadoActual = RX;
    PIN_LED1=1;
    tInicio = tickRead();                   
}
void ActualizarMEF(void){
    static uint8_t res;
    static uint8_t aux;
    switch (estadoActual) {
        case RX:
            RxMode();
            if (uartReadByte(&res)) {
                if (res == RELE1_ON_ADDR || res == RELE2_ON_ADDR || res == RELE1_OFF_ADDR || res == RELE2_OFF_ADDR || res == RELE1_ASK_ADDR || res == RELE2_ASK_ADDR) 
                    {
                    estadoActual = ACTION;
                } else {
                    res = 0;
                    estadoActual = RX;

                }
            }
            break;
        case ACTION:
            switch(res){
                case RELE1_ON_ADDR:
                    PIN_RELE1 = 1;
                    res=0;
                    TxMode();
                    uartWriteByte(OK);
                    while (!uartReadByte(&aux));
                    if (aux == OK) {
                        RxMode();
                        estadoActual = RX;
                    }
                    break;
                case RELE2_ON_ADDR:
                    TRIS_RELE2=1;
                    res=0;
                    TxMode();
                    uartWriteByte(OK);
                    while(!uartReadByte(&aux));
                    if(aux==OK){
                        RxMode();
                        estadoActual=RX;
                    }
                    estadoActual=RX;
                    break;    
                case RELE1_OFF_ADDR:
                    PIN_RELE1 = 0;
                    res=0;
                    TxMode();
                    uartWriteByte(OK);
                    while(!uartReadByte(&aux));
                    if(aux==OK){
                        RxMode();
                        estadoActual=RX;
                    }
                    break;    
                case RELE2_OFF_ADDR:
                    TRIS_RELE2=0;
                    res=0;
                    TxMode();
                    uartWriteByte(OK);
                    while(!uartReadByte(&aux));
                    if (aux == OK) {
                        RxMode();
                        estadoActual = RX;
                    }
                    break;
                case RELE1_ASK_ADDR:
                    if (PIN_RELE1 == 1) {
                        res = 0;
                        TxMode();
                        uartWriteByte(ITS_ON);
                        while (!uartReadByte(&aux));
                        if (aux == ITS_ON) {
                            RxMode();
                            estadoActual = RX;
                        }
                    }
                    if (PIN_RELE1 == 0) {
                        res = 0;
                        TxMode();
                        uartWriteByte(ITS_OFF);
                        while (!uartReadByte(&aux));
                        if (aux == ITS_OFF) {
                            RxMode();
                            estadoActual = RX;
                        }
                    }
                    break;
                case RELE2_ASK_ADDR:
                    if (TRIS_RELE2 == 1) {
                        res = 0;
                        TxMode();
                        uartWriteByte(ITS_ON);
                        while (!uartReadByte(&aux));
                        if (aux == ITS_ON) {
                            RxMode();
                            estadoActual = RX;
                        }
                    }
                    if (TRIS_RELE2 == 0) {
                        res = 0;
                        TxMode();
                        uartWriteByte(ITS_OFF);
                        while (!uartReadByte(&aux));
                        if (aux == ITS_OFF) {
                            RxMode();
                            estadoActual = RX;
                        }
                    }
                    break;
            }
    }
        

}



void TxMode(void){
    PIN_RE=0;
    PIN_DE=1;
    
}
void RxMode(void){
    PIN_RE=0;
    PIN_DE=0;
}

