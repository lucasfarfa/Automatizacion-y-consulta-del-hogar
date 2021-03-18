/*
 * File:   main.c
 * Author: FAMELI Tech
 *
 * Created on 18 de septiembre de 2019, 16:16
 */
#include <xc.h>        
#include <stdint.h>     
#include "system.h"     
#include "user.h"     





void main(void){
    uint16_t result = 0;
    uint8_t request;
    initApp();
    PIN_LED1 = 1;
    PIN_LED2 = 1;
    //I2C_Test();
    InicializarMEFI2C();
    InicializarMEFUART();
    
    while(1){
        ActualizarMEFI2C();
        ActualizarMEFUART();
//          result= I2C_ReadRegister2(I2C_ADDR_L, 0b00010001);//lee el valor de iluminacion
//        RxMode();
//        if(OERR){

//            OERR=0;
//            SPEN=0;
//            SPEN=1;
//            
//        }
//        if(uartReadByte(&request)){
//
//            if(request==LUX_ADDR){
//              
//                request=0;
//
//               TxMode();
//               uartWriteByte((uint8_t)(result>>8));
//                uartWriteByte((uint8_t)(result&0x00FF));
//                while(!TRMT||!TXIF);
//                RxMode();
//            }
//    }
}
}







