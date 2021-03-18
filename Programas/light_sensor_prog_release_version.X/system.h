/*
 * File:   system.h
 * Author: FAMELI Tech
 *
 * Created on 18 de septiembre de 2019, 16:16
 */
#ifndef SYSTEM_H
#define SYSTEM_H

#define SYS_FREQ        4000000L
#define _XTAL_FREQ      SYS_FREQ
#define FCY             SYS_FREQ/4

/* Definición de Bits de Configuración */

#pragma config FOSC = XT        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = ON       
#pragma config BOREN = OFF      
#pragma config LVP = OFF       
#pragma config CPD = OFF        
#pragma config WRT = OFF       
#pragma config CCPMX = RB0      
#pragma config CP = OFF         




#endif// SYSTEM_H