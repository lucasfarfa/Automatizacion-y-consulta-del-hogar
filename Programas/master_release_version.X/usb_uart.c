/*
 * File:   usb_uart.c
 * Author: g_fer
 *
 * Created on 12 de junio de 2019, 08:44
 */


#include <xc.h>
#include "usb_uart.h"


void USBuartConfig(void) {
    USBDeviceInit();
    USBDeviceAttach();
}

void USBuartWriteByte( uint8_t dato ){
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }
    
    if( USBIsDeviceSuspended() == true )
    {
        return;
    }
    
    if( USBUSARTIsTxTrfReady() == true ) {
        putUSBUSART(&dato, 1);
    }
    
    CDCTxService();
    __delay_ms(10);
    CDCTxService();
}

bit USBuartReadByte( uint8_t* receivedByte ){
    uint8_t numBytesRead = 0;
    
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return 0;
    }

    if( USBIsDeviceSuspended() == true )
    {
        return 0;
    }
    
    if( USBUSARTIsTxTrfReady() == true ) {
        numBytesRead = getsUSBUSART(receivedByte, 1);

        if( numBytesRead > 0 )
        {
            return 1;
        }
    }
    
    return 0;
}