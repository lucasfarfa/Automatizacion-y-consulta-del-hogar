#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "socket_client.h"
char* getenv();
int main(void){
   FILE *pFile;
   char caracter[100];
   char temp[1000];
   char buff,x;
   char msg[]="Hola Mundo";
   int s,v;
   uint16_t port2comm =8000;
   char * i = &temp[0];
   i= getenv("QUERY_STRING");
   if(strlen(i)!=0){
      s=init_client("localhost");
      do{
      v=connect_to_server(s,port2comm);
      port2comm++;
      }while(v==-1&&port2comm<8011);  //hace intentos de conexion desde el puyerto 8000 hasta el puerto 8011
      if(v==-1){
         perror("No hay ningun puerto a la escucha en el server indicado");
         exit(1);
      }
      
      send_to_server(s,i,strlen(i));
      //recv_from_server(s,temp,sizeof(temp));
      close_client(s);
   }
   
  pFile = fopen("index.html","r");
  fscanf( pFile,"%",caracter );
  if( pFile != NULL ) {
      printf("Content-type:text/html\n\n");
      while( fscanf(pFile,"%[^\n]",caracter)!=  EOF) {
         printf("%s", caracter);
      }
      
      fclose(pFile);
   } else {
      printf(
      "Content-type:text/html\n\n"
      "<html lang=\"\"es\"\">\n"
      "<head>\n"
      "<title>FaMeLi</title>\n"
      "</head>\n"
      "<body style=\"background-color: #000000; \">\n"
      "<div align=\"center\">\n"
      "<h1 style=\"color: #0000CC;text-align: center;\">FAMELI</h4>\n"
      "<h2 style=\"color: #0000CC;text-align: center;\">- 2019 -</h3>\n"
      "</div>\n"
      "<div align=\"center\">\n"
      "<h3 style=\"color: #0000CC;text-align: center;\">Terminal de datos</h3>\n"
      "<h3 style=\"color: #0000CC;text-align: center;\">Proyecto Final</h3>\n"
      "</div>\n"	
      "<div style=\"background-color: #009933;border:1px solid #CEDCEA;\" align=\"center\">\n"
      "<h3 style=\"color: #00FF00;text-align: center;\">Temperatura recibida: 00 C</h3>\n"
      "<div style=\"background-color: #009933;border:1px solid #CEDCEA;\" align=\"center\">\n"
      "<h3 style=\"color: #00FF00;text-align: center;\">Iluminacion recibida: 00 C</h3>\n"
      "</div>\n"
      "</div>\n"
      "<div align=\"center\" style=\"padding: 10px\">\n"
      "<img src=\"\\ecea.png\" alt=\"logo\" width=\"300\" height=\"300\" border=\"3\">\n"
      "</div>\n"
      "<form method = \"GET\" action=\"./pruebacgi.cgi\">\n"
      "<input type = \"radio\" name=\"equipo\" value=\"lampara\" checked><h2 style=\"color: #0000CC;\"> Lampara <br></h2>\n"
      "<input type = \"radio\" name=\"equipo\" value=\"aire\"> <h2 style=\"color: #0000CC;\">Aire <br></h2>\n"
      "<div align=\"center\"><input type=\"submit\" value=\"Ejecutar Cambios!\">\n"
      "</div>\n"
      "</form>\n"
      "</body>\n"
      "</html>\n"
      /*
      "<html>\n"
      "<form action=\"./hola.cgi\">\n"
      "<div><lachar temp[1000];
      char buff,x;
      char msg[]="Hola Mundo";
      int s,v;
      uint16_t port2comm =8000;
      char * i = &temp[0];
      i= getenv("QUERY_STRING");
      if(strlen(i)!=0){
         s=init_client("localhost");
         do{
         v=connect_to_server(s,port2comm);
         port2comm++;
         }while(v==-1&&port2comm<8011);  //hace intentos de conexion desde el puyerto 8000 hasta el puerto 8011
         if(v==-1){
            perror("No hay ningun puerto a la escucha en el server indicado");
            exit(1);
         }
         
         send_to_server(s,i,strlen(i));
         //recv_from_server(s,temp,sizeof(temp));
         close_client(s);
      }
      printf(
      "Content-type:text/html\n\n"
      "<html lang=\"\"es\"\">\n"
      "<head>\n"
      "<title>FaMeLi</title>\n"
      "</head>\n"
      "<body style=\"background-color: #000000; \">\n"
      "<div align=\"center\">\n"
      "<h1 style=\"color: #0000CC;text-align: center;\">FAMELI</h4>\n"
      "<h2 style=\"color: #0000CC;text-align: center;\">- 2019 -</h3>\n"
      "</div>\n"
      "<div align=\"center\">\n"
      "<h3 style=\"color: #0000CC;text-align: center;\">Terminal de datos</h3>\n"
      "<h3 style=\"color: #0000CC;text-align: center;\">Proyecto Final</h3>\n"
      "</div>\n"	
      "<div style=\"background-color: #009933;border:1px solid #CEDCEA;\" align=\"center\">\n"
      "<h3 style=\"color: #00FF00;text-align: center;\">Temperatura recibida: 00 C</h3>\n"
      "<div style=\"background-color: #009933;border:1px solid #CEDCEA;\" align=\"center\">\n"
      "<h3 style=\"color: #00FF00;text-align: center;\">Iluminacion recibida: 00 C</h3>\n"
      "</div>\n"
      "</div>\n"
      "<div align=\"center\" style=\"padding: 10px\">\n"
      "<img src=\"\\ecea.png\" alt=\"logo\" width=\"300\" height=\"300\" border=\"3\">\n"
      "</div>\n"
      "<form method = \"GET\" action=\"./pruebacgi.cgi\">\n"
      "<input type = \"radio\" name=\"equipo\" value=\"lampara\" checked><h2 style=\"color: #0000CC;\"> Lampara <br></h2>\n"
      "<input type = \"radio\" name=\"equipo\" value=\"aire\"> <h2 style=\"color: #0000CC;\">Aire <br></h2>\n"
      "<div align=\"center\"><input type=\"submit\" value=\"Ejecutar Cambios!\">\n"
      "</div>\nbel>Multiplicand 1: <input name=\"m\" size=\"5\"></label></div>\n"
      "<div><label>Multiplicand 2: <input name=\"n\" size=\"5\"></label></div>\n"
      "<div><input type=\"submit\" value=\"Multiply!\"></div>\n"

      "</html>\n"
      
      //);*/
      );
   }
   /*
char* ReadFile(char *filename){
            char *buffer = NULL;
            int string_size, read_size;
            FILE *handler = fopen(filename, "r");
            
            if (handler){
               fseek(handler, 0, SEEK_END);
               string_size = ftell(handler);
               rewind(handler);
               
               
}*/
   return 0;
}
