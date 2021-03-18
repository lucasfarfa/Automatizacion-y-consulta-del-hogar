#include "socket_server.h"
#include <unistd.h>


/*
 *
 * name: init_server
 * inicia el servidor asignandole la ip local.
 * intenta tomar el port especificado. Si logra tomarlo
 * comienza a escuchar dicho puerto.
 * @param port, puerto tcp a ser tomado
 * @return el socket asignado o -1 si falla
 *
 */


int init_server(uint16_t port){
    int s;
    s = socket(AF_INET, SOCK_STREAM,0);
    if (s != -1)
    {
      // Asigna el puerto indicado y una IP de la maquina
      address.sin_family = AF_INET;
      address.sin_port = htons(port);
      address.sin_addr.s_addr = htonl(INADDR_ANY);

      // Conecta el socket a la direccion local
      if( bind(s, (struct sockaddr*)&address, sizeof(address)) != -1)
      {
        printf("\n\aServidor ACTIVO escuchando en el puerto: %d\n",port);
        // Indicar que el socket encole hasta MAX_CONN pedidos
        // de conexion simultaneas.
        if (listen(s, MAX_CONN) < 0)
        {
          perror("Error en listen");
          exit(1);
        }
        return s;
      }
      else{
        return(-1);
      }

}
else{
    perror("El socket no se ha creado correctamente!\n");
    exit(1);
}
}

/*
 *
 * name: wait_untill_conn
 * esta funcion bloquea hasta que recibe un pedido de conexion.
 * De ser asi la acepta y crea un nuevo socket de dialogo.
 * @param socket s donde debe esperar conexiones.
 * @return el socket s_aux producto de la conexion aceptada.
 *
 */


int wait_untill_conn(int s){
        fd_set readfds;
        int s_aux;
        do{
          // Crear la lista de "file descriptors" que vamos a escuchar
          FD_ZERO(&readfds);

          // Especificamos el socket, podria haber mas.
          FD_SET(s, &readfds);

          // Espera al establecimiento de alguna conexion.
          // El primer parametro es el maximo de los fds especificados en
          // las macros FD_SET + 1.
          nbr_fds = select(s+1, &readfds, NULL, NULL, NULL);

          if ((nbr_fds<0) && (errno!=EINTR))
          {
            perror("select");
            exit(1);
          }
        }
          while(!FD_ISSET(s,&readfds));
          addrlen = sizeof(address);
          if ((s_aux = accept (s, (struct sockaddr*) &address, &addrlen)) < 0)// en addlen le estoy pasando la longitud de la direccion esperada (IPV4 o IPV6)
          {
            perror("Error en accept");
            exit(1);
          }
          return s_aux;
}

/*
 *
 * name: recv_from_client
 * recibe datos desde el cliente ya aceptado.
 * @param s socket devuelto en wait_untill_conn, data vector de datos char(o uint8_t)
 * y number_of_bytes que son la cantidad de bytes a recibir
 * @return numero de bytes recibidos.
 *
 */


int recv_from_client(int s, char* data, uint16_t number_of_bytes){
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
 * name: send_to_client
 * envia datos al cliente ya aceptado.
 * @param s socket devuelto en wait_untill_conn, data vector de datos char(o uint8_t)
 * y number_of_bytes que son la cantidad de bytes a enviar
 * @return numero de bytes enviados.
 *
 */
int send_to_client(int s, char* data, uint16_t number_of_bytes){
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
 * name: close_socket
 * cierra un socket de conexion.
 * @param s socket a ser cerrado.
 *
 */
void close_socket(int s){
    close(s);
}



