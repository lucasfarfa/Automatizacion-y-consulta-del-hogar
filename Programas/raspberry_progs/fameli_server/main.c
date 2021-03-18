#include <stdio.h>
#include <stdlib.h>
#include "my_sem.h"
#include "my_shmem.h"
#include <unistd.h>
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <string.h>         //para usar strlen
#include "serial_port.h"
#include <signal.h>
#include <time.h>
#include "socket_client.h"
#include "socket_server.h"

//------------MAIN PROGRAM------------------//

void SIGCLD_HANDLER(void)
{
    int waitstatus;
    waitpid(-1,&waitstatus,WNOHANG);
    //wait(&waitstatus);
}
int main()
{
    int s,s_aux,pid,tam;
    uint8_t buffer[10];
    uint16_t port2open=8000;//puerto inicial a abrir ADDRECENT
    char dato = 0xAA;
    char tecla;
    unsigned char entrada[20];// vector de datos de entrada ADDRECENT
    unsigned char salida[]="Recibido"; //mensaje a ser enviado ADDRECENT
    tam = init_shmem(100);
    printf("%d",tam);
    write_byte_shmem(1,0);
    init_sem(1,VERDE);
    signal(SIGCLD,(__sighandler_t)SIGCLD_HANDLER); //se hace una sola vez entonces va fuera del while HACE EL CODIGO DE ARRIBA VOID
    //while(1)        // ADDRECENT
    // {
    pid = fork();            //si llega crea un proceso hijo que dialogue con dicha conexion a traves del socket s_aux
    if(pid == 0)    //si soy el hijo SE OCUPA DE LA SM Y PS
    {
        char rx;

        uint8_t data,cuenta=0;
        uint32_t timeout;
        int count,i ;
        int rx_length;
        char circ_buffer[5] = {0,0,0,0,0};
        unsigned char circ_buffer2[5] = {0,0,0,0,0};
        char cant=0,cant2=0;

        //   EL PROCESS ID DEL HIJO ES 0

        if (open_uart() == -1)
        {
            printf("Error en abrir el puerto serie\n");
            exit(0);
        }
        printf("Puerto Serie abierto con exito\n");
        uartConfig();
        while(1)
        {
            usleep(50000);//duermo 50 mseg
            cuenta++;
            //  printf("%d\n",cuenta);
            if(read_byte_shmem(50)) //hay actualizacion de hw?
            {
                write_byte_shmem(50,0);
                if(read_byte_shmem(51))
                {
                    data=0xC1;
                    uartWriteByte(data);
                }
                else
                {
                    data=0xC3;
                    uartWriteByte(data);
                }
                if(read_byte_shmem(52))
                {
                    data=0xC2;
                    uartWriteByte(data);
                }
                else
                {
                    data=0xC4;
                    uartWriteByte(data);
                }

            }
            if(cuenta==15)
            {

                cuenta=0;
                timeout=0;
                dato = 0x66;
                buffer[0]=0;
                buffer[1]=0;
                buffer[2]=0;
                buffer[3]=0;
                buffer[4]=0;
                buffer[5]=0;
                fflush(stdout);
                count = uartWriteByte(dato);
                if(count==0)
                {
                    printf("error 1\n") ;
                }
                i=0;

                while(!uartReadByte(&rx));
                if(rx==0xFC)
                {
                    for(i=0; i<6; i++)
                    {
                        while(!uartReadByte(&buffer[i]));
                    }
                    while(!uartReadByte(&rx));
                    if(rx==0xFE)
                    {
                        //  printf("%x %x %x %x %d\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
                    }
                    take_sem(0);            // SEMAFORO EN ROJO PARA QUE NO ACCEDA EL PADRE
                    //Bytes received
                    write_byte_shmem(0,buffer[0]);
                    write_byte_shmem(1,buffer[1]);
                    write_byte_shmem(2,buffer[2]);
                    write_byte_shmem(3,buffer[3]);
                    write_byte_shmem(4,buffer[4]);
                    write_byte_shmem(5,buffer[5]);
                    write_byte_shmem(10,1); //en 1 pongo un 1 cuando hay un dato NUEVO
                    free_sem(0);            // TERMINO CON EL SEMAFORO
                }
            }
        }
    }
    else //si soy el padre
    {
        do
        {
            s=init_server(port2open); //intenta iniciar el server en el puerto inicial, si no puede incrementa el puerto y sigue intentando
            port2open++;
        }
        while(s==-1);
        while(1)
        {
            s_aux =wait_untill_conn(s);// espera una conexion,
            pid=fork();// si llega crea un proceso hijo que dialogue con dicha conexion a traves del socket s_aux
            if(pid==0)  // si soy el hijo...
            {
                char rx2;
                recv_from_client(s_aux,entrada,sizeof(entrada)); //recibo
                send_to_client(s_aux,buffer,6);
                entrada[15]=0;
                if(entrada[0]=='l')
                {
                    take_sem(0);
                    write_byte_shmem(50,1);//hay actualizacion de hardware
                    write_byte_shmem(51,!(read_byte_shmem(51)));
                    free_sem(0);
                }
                if(entrada[0]=='a')
                {
                    take_sem(0);
                    write_byte_shmem(50,1);//hay actualizacion de hardware
                    write_byte_shmem(52,!(read_byte_shmem(52)));
                    free_sem(0);
                }
                if(entrada[0]=='R'||entrada[0]=='a'||entrada[0]=='l')
                {
                }
                close_socket(s_aux);//cierro la conexion
                exit(0);//me muero
            }
            else // si soy el padre...
            {
                take_sem(0);
                //  write_byte_shmem(4,0); //ahora el dato es viejo
                if(read_byte_shmem(10))
                {
                    write_byte_shmem(10,0);
                    buffer[0]=read_byte_shmem(0);
                    buffer[1]=read_byte_shmem(1);
                    buffer[2]=read_byte_shmem(2);
                    buffer[3]=read_byte_shmem(3);
                    buffer[4]=read_byte_shmem(4);
                    buffer[5]=read_byte_shmem(5);
                }
                free_sem(0);
                // buffer[2]=read_byte_shmem(2);
                close_socket(s_aux);// cierro mi s_aux, pues quien dialoga ahora es el hijo.
                //vuelvo al ciclo del while
            }
        }
    }

    close_socket(s); //ADDRECENT
    return (0);
}
