#include "socket_client.h"

/*
 *
 * name: init_client
 * inicializa el cliente, poniendo como objetivo
 * la direccion cuyo nombre de dominio se especifica
 * @param server, es el nombre de dominio al que deseo comunicarme
 * Ej "localhost" o "google.com"
 * @return el socket generado por este proceso. -1 si falla.
 *
 */


int init_client(char* server){
  int conexion;
  servidor = gethostbyname(server); //Asignacion
  if(servidor == NULL)
  { //Comprobación
    printf("Host erróneo\n");
    return -1;
  }
  conexion = socket(AF_INET, SOCK_STREAM, 0); //Asignación del socket

  return conexion;
}



/*
 *
 * name: connect_to_server
 * conecta la aplicacion al servidor apuntado en init_client
 * mediante el puerto especificado
 * @param s socket devuelto por init_client, port puerto del server
 * al que quiero comunicarme
 * @return 0 si esta ok, -1 si el server rechaza la conexion
 *
 */


int connect_to_server(int s,uint16_t port){
  int puerto=(port); //conversion del argumento
  bzero((char *)&cliente, sizeof((char *)&cliente)); //Rellena toda la estructura de 0's
        //La función bzero() es como memset() pero inicializando a 0 todas la variables
  cliente.sin_family = AF_INET; //asignacion del protocolo
  cliente.sin_port = htons(puerto); //asignacion del puerto
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
  //bcopy(); copia los datos del primer elemendo en el segundo con el tamaño máximo
  //del tercer argumento.
  if(connect(s,(struct sockaddr *)&cliente, sizeof(cliente)) < 0)
  { //conectando con el host
    perror("Error conectando con el host\n");
    return -1;

  }
  else{
    return 0;
  }
}


/*
 *
 * name: send_to_server
 * envia datos al servidor que ya acepto la conexion.
 * @param s socket devuelto en init_client, data vector de datos char(o uint8_t)
 * y number_of_bytes que son la cantidad de bytes a enviar
 * @return numero de bytes enviados.
 *
 */

int send_to_server(int s, char* data, uint16_t number_of_bytes){
    int rv;
    if (rv=send(s,data,number_of_bytes, 0) == -1)
          {
            perror("Error en send");
            exit(1);
          }
    return rv;

}
/*
 *
 * name: recv_from_client
 * recibe datos desde el servidor que ya acepto la conexion.
 * @param s socket devuelto en init_client, data vector de datos char(o uint8_t)
 * y number_of_bytes que son la cantidad de bytes a recibir
 * @return numero de bytes recibidos.
 *
 */
int recv_from_server(int s, char* data, uint16_t number_of_bytes){
    int rv;
    if (rv=recv(s,data,number_of_bytes, 0) == -1)
          {
            perror("Error en recv");
            exit(1);
          }
    return rv;

}

/*
 *
 * name: close_client
 * cierra un socket de conexion.
 * @param s socket a ser cerrado.
 *
 */
void close_client(int s){
    close(s);
}
