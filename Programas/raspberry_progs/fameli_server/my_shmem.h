#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdint.h>

static int shmid;
static key_t key;
static void* shared_mem= (void*)NULL;
static uint8_t* _8ptr;
static uint16_t* _16ptr;
static uint32_t* _32ptr;




unsigned int init_shmem(unsigned int tam);
uint8_t read_byte_shmem(unsigned int idx);
void write_byte_shmem(unsigned int idx, uint8_t valor);
uint16_t read_word_shmem(unsigned int idx);
void write_word_shmem(unsigned int idx, uint16_t valor);
uint32_t read_dword_shmem(unsigned int idx);
void write_dword_shmem(unsigned int idx, uint32_t valor);
void free_shmem(void);



