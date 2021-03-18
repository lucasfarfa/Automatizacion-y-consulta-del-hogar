// CODIGO HECHO POR FAMELI
#include <xc.h>        
#include <stdint.h>     
#include "system.h"     
#include "user.h"       


void InicializarMEF(void);
void ActualizarMEF(void);

void main(void){
    initApp(); 
    InicializarMEF();
    while(1){
    ActualizarMEF();
    }
}
