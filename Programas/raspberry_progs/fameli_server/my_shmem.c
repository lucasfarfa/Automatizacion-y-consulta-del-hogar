#include <stdio.h>
#include <stdint.h>
#include "my_shmem.h"

/** \brief init_shmem pide al sistema operativo
 *         una determinada cantidad de memoria
           compartida
 * \param  tam: cantidad de bytes de memoria requeridos
 *         la funcion automaticamente lo ajusta al multiplo
 *         de 4 mas cercano. el tamaño maximo es 65532 bytes
 * \return el tamaño de la memoria obtenida en bytes. Debe usarse para proteger
 *         el acceso a la memoria.
 */

unsigned int init_shmem(unsigned int tam){
        if(tam>65532)
            tam=65532;
        else{
        if((tam%4)){
            tam+=(4-(tam%4));//vuelvo el tamaño multiplo de 4 bytes
        }
        }
        if ((key = ftok("/bin/ls", "PO")) == -1) {
         perror("ftok");
         exit(1);
        }// pido una clave para la memoria
        shmid = shmget( key, (size_t)tam, 0600 | IPC_CREAT);
        shared_mem =  shmat(shmid, (void *)0, 0); //apunto a la memoria compartida
        _8ptr = (unsigned char *)shared_mem;
        _16ptr = (unsigned char *)shared_mem;
        _32ptr = (unsigned char *)shared_mem;
        return tam;
}


/** \brief read_byte_shmem lee un byte de la memoria
 *         compartida
 * \param `idx:es la posicion de donde se desea leer.
 *         debe entenderse como si la memoria compartida fuese un
 *         vector de bytes
 *         idx no debe superar a tam-1
 *
 * \return el valor del byte leido.
 *
 */

uint8_t read_byte_shmem(unsigned int idx){
return *(_8ptr+idx);
}


/** \brief write_byte_shmem escribe un byte de la memoria
 *         compartida
 * \param `idx:es la posicion de donde se desea escribir.
 *         debe entenderse como si la memoria compartida fuese un
 *         vector de bytes
 *         idx no debe superar a tam-1
 */

void write_byte_shmem(unsigned int idx, uint8_t valor){
*(_8ptr+idx)=valor;
}


/**\brief  read_word_shmem lee dos bytes (un uint16_t) de la memoria
 *         compartida
 * \param `idx:es la posicion de donde se desea leer.
 *         debe entenderse como si la memoria compartida fuese un
 *         vector de uint16_t
 *         idx no debe superar a (tam/2)-1
 *
 * \return el valor del uint16_t leido.
 *
 */

uint16_t read_word_shmem(unsigned int idx){
return *(_16ptr+idx);
}


/**\brief  write_word_shmem escribe dos bytes (un uint16_t) de la memoria
 *         compartida
 * \param `idx:es la posicion de donde se desea escribir.
 *         debe entenderse como si la memoria compartida fuese un
 *         vector de uint16_t
 *         idx no debe superar a (tam/2)-1
 */

void write_word_shmem(unsigned int idx, uint16_t valor){
*(_16ptr+idx)=valor;
}

/**\brief  read_dword_shmem lee cuatro bytes (un uint32_t) de la memoria
 *         compartida
 * \param `idx:es la posicion de donde se desea leer.
 *         debe entenderse como si la memoria compartida fuese un
 *         vector de uint32_t
 *         idx no debe superar a (tam/4)-1
 *
 * \return el valor del uint32_t leido.
 *
 */
uint32_t read_dword_shmem(unsigned int idx){
return *(_32ptr+idx);
}

/**\brief  write_dword_shmem escribe cuatro bytes (un uint32_t) de la memoria
 *         compartida
 * \param `idx:es la posicion de donde se desea escribir.
 *         debe entenderse como si la memoria compartida fuese un
 *         vector de uint32_t
 *         idx no debe superar a (tam/4)-1
 */

void write_dword_shmem(unsigned int idx, uint32_t valor){
*(_32ptr+idx)=valor;
}

/** \brief free_shmem libera la memoria compartida.
 *
 */

void free_shmem(void){
shmdt(shared_mem);
}
