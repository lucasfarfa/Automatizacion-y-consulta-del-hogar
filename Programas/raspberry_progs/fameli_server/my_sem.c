#include <stdio.h>
#include "my_sem.h"
//

/** \brief init_sem pide al sistema operativo
 *         un vector de semaforos y los inicializa
 *         en un valor determinado.
 *
 * \param cant es la cantidad de semaforos en el vector
 * \param valor es el valor en que deben ser inicializados (ROJO o VERDE)
 *
 * \return la cantidad de semaforos en el vector, debe usarse para proteger el acceso.
 */

unsigned int init_sem(unsigned int cant, int valor){
    int i;
    if ((key = ftok("/bin/ls", 'J')) == -1) {
         perror("ftok");
         exit(1);
	}// pido una clave para el semaforo

    if ((semid = semget(key, cant, IPC_CREAT | 0600)) == -1) {
         perror("semget");
         exit(1);
    }//obtengo un semaforo con la clave

    arg.val = valor;
    for(i=0;i<cant;i++){
	if (semctl(semid, i, SETVAL, arg) == -1) {
            perror("semctl");
            exit(1);
	}// lo configuro como binario
    }
    return cant;
}

/** \brief take_sem toma el semaforo indicado en number,
 *          si ya esta en rojo bloquea,
 *          si no puede sale del programa
 *
 * \param  number es el numero de semaforo a tomar
 *         no debe superar a cant-1
 */

void take_sem(unsigned short int number){
    sb.sem_op = -1; /* tomo el semaforo, si otro proceso quiere tomarlo se bloquea */
    sb.sem_num = number;
    if (semop(semid, &sb, 1) == -1) {
    perror("semop");
    exit(1);
    }
}
/** \brief  free_sem libera el semaforo indicado en number,
 *          si no puede sale del programa
 *
 * \param  number es el numero de semaforo a liberar
 *         no debe superar a cant-1
 */
void free_sem(unsigned short int number){
    sb.sem_op = 1; /* tomo el semaforo, si otro proceso quiere tomarlo se bloquea */
    sb.sem_num = number;
    if (semop(semid, &sb, 1) == -1) {
    perror("semop");
    exit(1);
    }
}
