#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include "my_sem.h"
#include "my_shmem.h"
#include "socket_server.h"



void manejadorSIGCHLD(int sig){

 while(waitpid(-1,NULL,WNOHANG)>0); //sirve para finalizar el proceso hijo de manera correcta
}

int main(int argc, char *argv[])
{

	 int s,s_aux;
	 int pid;
	 uint16_t port2open=8000;//puerto inicial a abrir
	 unsigned char entrada[20];// vector de datos de entrada
	 unsigned char salida[]="Recibido"; //mensaje a ser enviado
	 signal(SIGCHLD,(__sighandler_t)manejadorSIGCHLD); //sirve para finalizar el proceso hijo de manera correcta
	 do{s=init_server(port2open); //intenta iniciar el server en el puerto inicial, si no puede incrementa el puerto y sigue intentando
     port2open++;
	 }
	 while(s==-1);
	 while(1){
		s_aux =wait_untill_conn(s);// espera una conexion, 
		pid=fork();// si llega crea un proceso hijo que dialogue con dicha conexion a traves del socket s_aux 
		if(pid==0){ // si soy el hijo...
			recv_from_client(s_aux,entrada,sizeof(entrada)); //recibo...
			printf("%s\n",entrada); //imprimo lo recibido
			send_to_client(s_aux,salida,strlen(salida));//contesto...
			close_socket(s_aux);//cierro la conexion
			exit(0);//me muero
		}
		else{// si soy el padre...
			close_socket(s_aux);// cierro mi s_aux, pues quien dialoga ahora es el hijo.
			//vuelvo al ciclo del while
		}
	 }
     close_socket(s);
}
