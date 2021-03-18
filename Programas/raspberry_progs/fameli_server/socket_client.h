#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdint.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <stdint.h>


static struct sockaddr_in cliente; //Declaración de la estructura con información para la conexión
static struct hostent *servidor; //Declaración de la estructura con información del host

int init_client(char* server);
int connect_to_server(int s,uint16_t port);
int send_to_server(int s,char* data,uint16_t number_of_bytes);
int recv_from_server(int s,char* data, uint16_t number_of_bytes);
void close_client(int s);

