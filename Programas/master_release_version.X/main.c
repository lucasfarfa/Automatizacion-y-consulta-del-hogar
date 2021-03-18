
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



/*#if defined(USB_INTERRUPT)
void interrupt SYS_InterruptHigh(void)
{
    USBDeviceTasks();
}
#endif
 * */



void main(void)
{ 
    uint8_t byte;
    uint32_t tick = 0;
    
    USBuartConfig();
    initApp();
    tick_t tinicio, tloop;
    tinicio=tickRead();
    uint8_t n,x=0,data[2];
    initApp();        
    PIN_LED1 = 0;
    PIN_LED2 = 0;
    PIN_LED3 = 0;
    PIN_LED4 = 1;
    IniciarMasterMEF();
    while(1) {
        ActualizarMasterMEF();
    
//        if( USBGetDeviceState() < CONFIGURED_STATE && (tickRead()-tinicio>=500) ) {
//            PIN_LED2 = !PIN_LED2;
//            tinicio=tickRead();
//        }
//        
//       // x++;
//        //USBuartReadByte(&n);
//        //if(n == 0xEE){
//        n=0xA8; //lux id //n=0xDA;
//        TxMode();
//        uartWriteByte(n);
//        while(!TRMT);
//        RxMode();
//        while(!uartReadByte(&data[0]));
//        while(!uartReadByte(&data[1]));
//        PIN_LED1 = !PIN_LED1;
//            //if (n == 0xAA){  
//        PIN_LED3 = 1;
//            //while (n == 0xAA);
//            //PIN_LED3 = 0;
//           //}
//        n=0;
//        //}     
    }


}


void initCDC()
{   
    line_coding.bCharFormat = 0;
    line_coding.bDataBits = 8;
    line_coding.bParityType = 0;
    line_coding.dwDTERate = 9600;
}




