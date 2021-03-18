/*
 * File:   DHT11.c
 * Author: g_fer
 *
 * Created on 27 de agosto de 2019, 08:05
 */


#include <xc.h>
#include <stdint.h>
#include "DHT11.h"
#include "user.h"
#include "system.h"


bit DHT11StartSignal(void){
    tick_t tinicio;
    DHT11Output();
    DHT11SetLow();
    tinicio= tickRead();
    while(tickRead()-tinicio<19);
  DHT11Input();
    __delay_us(30);
    if(PIN_DHT11==0){
        return 1;
    }
    else
        return 0;
    
}

bit DHT11CheckResponse(void){
     DHT11Input();
     TMR2=0;
     TMR2ON=1;
     while(PIN_DHT11==0);
     TMR2ON=0;
     if(TMR2<50)
         return 0;
     TMR2=0;
     TMR2ON=1;
     while(PIN_DHT11==1);
     TMR2ON=0;
     if(TMR2<60)
     return 0; 
     return 1;
}
    
 bit DHT11ReadByte(uint8_t* data){
     *data = 0;
     uint8_t i;
     for(i=0;i<8;i++){
     while(PIN_DHT11==0);
     TMR2=0;
     TMR2ON=1;
     while(PIN_DHT11==1);
     TMR2ON=0;
     if(TMR2>40){
       *data|=1<<(7-i);
     }
     
 }
  return 1;   
 }
         
     
     
    
