/*
 * File:   MasterMeF.c
 * Author: g_fer
 *
 * Created on 26 de septiembre de 2019, 10:40
 */


#include <xc.h>
#include <stdbool.h>

#include "usb_config.h"
#include "usb_device.h"
#include "usb_device_cdc.h"
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* For uint8_t definition */
#include "system.h"     /* Funciones/Parametros System, como osc/peripheral config */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "usb_uart.h"
#include "MasterMeF.h"

static estadoMaster estadoActual;
static tick_t tinicio,timeout,tloop;
static uint8_t next;

struct pantalla{
    uint8_t luz[2];
    uint8_t temp;
    uint8_t relstates[2];
    uint8_t hum;
} ;

union paquete{
    struct pantalla estructura;
    uint8_t bytes[5];
};
void IniciarMasterMEF(void){
    estadoActual = INICIAL;
    tinicio=tickRead();
    tloop=tickRead();
}

void ActualizarMasterMEF(void) {
    union paquete pkg;
    static uint8_t target, data, lux[2], i, aux, temp, datousb;
    switch (estadoActual) {
        case INICIAL:
            if (USBGetDeviceState() < CONFIGURED_STATE && (tickRead() - tinicio >= 500)) {
                PIN_LED2 = !PIN_LED2;
                tinicio = tickRead();
            } else {
                tloop = tickRead();
                estadoActual = USB_RX; // esto es para probar
            }
            break;
        case UART_TX:
            TxMode();
            uartWriteByte(target);
            while (!uartReadByte(&aux));
            if (aux == target) {
                aux = 0;
                RxMode();
                estadoActual = UART_RX;
                i = 0;
                timeout = tickRead();
            } else {
                estadoActual = UART_TX;
            }
            break;
        case UART_RX:
            switch(target){
                case LUX_ADDR:
                    if (uartReadByte(&data) && i < 2) {
                        lux[i] = data;
                        timeout = tickRead();
                        i++;
                    } else {
                        if (i >= 2) {
                            if(lux[0]&0x40){
                                lux[0]&=0xBF;
                                lux[1]|=0x80;
                            }
                            estadoActual = UART_TX;
                        pkg.estructura.luz[0]=lux[0];        
                        pkg.estructura.luz[1]=lux[1];  
                        target=TEMP_ADDR;
                        }
                        if (tickRead() - timeout > 500) {
                            estadoActual = INICIAL;
                        }
                    }
                    break;
                case RELE1_ASK_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data;
                        timeout = tickRead();       
                        pkg.estructura.relstates[0]=temp;
                        estadoActual = UART_TX;
                        target = RELE2_ASK_ADDR;
                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;
                case RELE2_ASK_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data;
                        timeout = tickRead();
                        pkg.estructura.relstates[1]=temp;
                        estadoActual = INICIAL;
                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;
                    
                case TEMP_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data;
                        timeout = tickRead();
                        pkg.estructura.temp=temp;
                        target = HUM_ADDR;
                        estadoActual = UART_TX;
                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;

                case HUM_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data;
                        timeout = tickRead();
                        pkg.estructura.hum=temp;
                        target = RELE1_ASK_ADDR;
                        estadoActual = UART_TX;
                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;

                case RELE1_ON_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data; // esto debiera ser el ok
                        if (temp == 0xC8) {
                            timeout = tickRead();
                            estadoActual = INICIAL;
                        } else {
                            target = RELE1_ON_ADDR;
                            estadoActual = UART_TX;
                        }

                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;
                case RELE1_OFF_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data; // esto debiera ser el ok
                        if (temp == 0xC8) {
                            timeout = tickRead();
                            estadoActual = INICIAL;
                        } else {
                            target = RELE1_OFF_ADDR;
                            estadoActual = UART_TX;
                        }

                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;
                case RELE2_ON_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data; // esto debiera ser el ok
                        if (temp == 0xC8) {
                            timeout = tickRead();
                            estadoActual = INICIAL;
                        } else {
                            target = RELE2_ON_ADDR;
                            estadoActual = UART_TX;
                        }

                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;
                case RELE2_OFF_ADDR:
                    if (uartReadByte(&data)) {
                        temp = data; // esto debiera ser el ok
                        if (temp == 0xC8) {
                            timeout = tickRead();
                            estadoActual = INICIAL;
                        } else {
                            target = RELE2_OFF_ADDR;
                            estadoActual = UART_TX;
                        }

                    } else if (tickRead() - timeout > 500) {
                        estadoActual = INICIAL;
                    }
                    break;
            }
            break;
        case USB_RX:
            if (USBuartReadByte(&datousb)) {
                if (datousb == RELE1_ON_ADDR) {
                    estadoActual = UART_TX;
                    target = RELE1_ON_ADDR;
                }
                else if (datousb == RELE1_OFF_ADDR) {
                    estadoActual = UART_TX;
                    target = RELE1_OFF_ADDR;
                }
                else if (datousb == RELE2_ON_ADDR) {
                    estadoActual = UART_TX;
                    target = RELE2_ON_ADDR;
                }
                else if (datousb == RELE2_OFF_ADDR) {
                    estadoActual = UART_TX;
                    target = RELE2_OFF_ADDR;
                }
                else if (datousb == 0x66) {
                    estadoActual = USB_TX;
                }
            } else {
                if(tickRead()-tloop>500){
                tloop=tickRead();    
                estadoActual = UART_TX;
                target = LUX_ADDR;
                }
            }
            break;
            
        case USB_TX:
            USBuartWriteByte(0xFC); //inicio de transmision
            USBuartWriteByte(pkg.bytes[0]); //primer byte de lux
            USBuartWriteByte(pkg.bytes[1]);//segundo byte de lux
            USBuartWriteByte(pkg.bytes[2]);//temperatura
            USBuartWriteByte(pkg.bytes[3]);//estado del primer rele
            USBuartWriteByte(pkg.bytes[4]);//estado del segundo rele
            USBuartWriteByte(pkg.bytes[5]);//humedad
            USBuartWriteByte(0xFE);
            estadoActual=INICIAL;
            break;
    }
}
