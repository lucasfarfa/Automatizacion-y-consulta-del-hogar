// CODIGO HECHO POR FAMELI
#ifndef SYSTEM_H
#define SYSTEM_H

#define SYS_FREQ        4000000L
#define _XTAL_FREQ      SYS_FREQ
#define FCY             SYS_FREQ/4

/* Definición de Bits de Configuración */

#pragma config FOSC = INTOSCIO      
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = OFF 
#pragma config CP = OFF     
#pragma config CPD = OFF    
#pragma config BOREN = OFF  

#pragma config LVP = OFF




#endif// SYSTEM_H