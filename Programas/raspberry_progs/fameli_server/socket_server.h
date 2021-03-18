#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <stdint.h>
#define MAX_CONN 10 //Nro maximo de conexiones en espera

static int nbr_fds;
static struct sockaddr_in address;
static char ipAddr[20];
static int Port;
static socklen_t addrlen;



int init_server(uint16_t port);
int wait_untill_conn(int s);
int send_to_client(int s,char* data,uint16_t number_of_bytes);
int recv_from_client(int s,char* data, uint16_t number_of_bytes);
void close_socket(int s);
