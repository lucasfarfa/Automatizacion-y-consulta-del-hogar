#include <sys/sem.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define ROJO 0
#define VERDE 1

union semun {
      int              val;    /* Value for SETVAL */
      struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
      unsigned short  *array;  /* Array for GETALL, SETALL */
      struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux specific) */
};

static  union semun arg;
static  int semid;
static	struct sembuf sb = {0, -1, 0};  /* arrancar en lock */
static  key_t key;



unsigned int init_sem(unsigned int cant, int valor);
void take_sem(unsigned short int number);
void free_sem(unsigned short int number);

