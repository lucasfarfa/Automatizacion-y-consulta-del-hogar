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
int main(void)
{
    char temp[1000],aux[20];
    unsigned char lux[2];
    uint16_t lux16;
    char color0[]="#66ff99";
    char color1[]="#ff8080";
    char buff,x;
    char msg[]="Hola Mundo";
    int s,v;
    int num;
    FILE * arch;
    uint16_t port2comm;
    char * i = &temp[0];
    aux[0]=0;
    i= getenv("QUERY_STRING");
    arch = fopen("port.ini","r");
    if(arch == NULL){
       printf("Content-type:text/html\n\n"
        "<html>"
        "<head>"
        "Error"
        "</head>"
        "<h1>No encuentro el archivo</h1>"
        "</html>");
        return -1;
     }
    fscanf(arch,"%d", &port2comm);
    fclose(arch);

    if(strlen(i)!=0)
    {
        s=init_client("localhost");
        v=connect_to_server(s,port2comm);
        if(v==-1) printf("no conecta");
        send_to_server(s,i,strlen(i));
        recv_from_server(s,aux,6);
        lux16 = 0;
        lux16 = aux[0];
        lux16 <<= 8;
        lux16 += aux[1];
        close_client(s);
        if(aux[3]==0x75){
           strcpy(color0,"#66ff99");
        }
        else if(aux[3]==0x79){
          strcpy(color0,"#ff8080"); 
        }
        if(aux[4]==0x75){
           strcpy(color1,"#66ff99");
        }
        else if(aux[4]==0x79){
          strcpy(color1,"#ff8080"); 
        }
    }
    printf(
        "Content-type:text/html\n\n"
        "<html>"
        "<head>"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        "<title>FaMeLi Tech&#174 </title>"
        "<style>"
         
        "* {"
        "box-sizing: border-box;"
        "}"

        ".row::after {"
        "content: \"\";"
        "clear: both;"
        "display: table;"
        "}"

        "[class*=\"col-\"] {"
        "float: left;"
        "padding: 15px;"
        "}"

        "html {"
        "font-family: \"Helvetica\", sans-serif;"
        "background-color: #8a8a8a;"
        "}"

        ".header {"
        "background-color: #ffdddd;"
        "color: #6f3e3e;"
        "padding: 15px;"
        "text-align: center;"
        "border-radius: 5px;"
        "}"

        ".aside {"
        "background-color: #ce9c6f;"
        "padding: 15px;"
        "color: white;"
        "text-align: center;"
        "font-size: 14px;"
        "box-shadow: 0 1px 3px rgba(0,0,0,0.12), 0 1px 2px rgba(0,0,0,0.24);"
        "border-radius: 5px;"
        "}"

        ".footer {"
        "background-color: #ffdddd;"
        "color: #6f3e3e;"
        "border-radius: 5px;"
        "text-align: center;"
        "font-size: 16px;"
        "font-weight: bold;"
        "padding: 15px;"
        "}"

        ".button_lamp {"
        "background-color: %s;"
        "border-radius: 12px;"
        "color: #6f3e3e;"
        "font-weight: bold;"
        "padding: 13.5px 32px;"
        "text-align: center;"
        "display: inline-block;"
        "font-size: 20px;"
        "cursor: pointer;"
        "}"

        ".button_vent {"
        "background-color: %s;"
        "border-radius: 12px;"
        "color: #6f3e3e;"
        "font-weight: bold;"
        "padding: 13.5px 32px;"
        "text-align: center;"
        "display: inline-block;"
        "font-size: 20px;"
        "cursor: pointer;"
        "}"
        
        ".button_refresh {"
        "background-color: #ffdddd;"
        "border-radius: 12px;"
        "color: #6f3e3e;"
        "font-weight: bold;"
        "padding: 13.5px 32px;"
        "text-align: center;"
        "display: inline-block;"
        "font-size: 20px;"
        "cursor: pointer;"
        "}"

        "[class*=\"col-\"] {"
        "width: 100%;"
        "}"

        "@media only screen and (min-width: 600px) {"
        ".col-s-1 {width: 8.33%;}"
        ".col-s-2 {width: 16.66%;}"
        ".col-s-3 {width: 25%;}"
        ".col-s-4 {width: 33.33%;}"
        ".col-s-5 {width: 41.66%;}"
        ".col-s-6 {width: 50%;}"
        ".col-s-7 {width: 58.33%;}"
        ".col-s-8 {width: 66.66%;}"
        ".col-s-9 {width: 75%;}"
        ".col-s-10 {width: 83.33%;}"
        ".col-s-11 {width: 91.66%;}"
        ".col-s-12 {width: 100%;}"
        "}"
        "@media only screen and (min-width: 768px) {"
        ".col-1 {width: 8.33%;}"
        ".col-2 {width: 16.66%;}"
        ".col-3 {width: 25%;}"
        ".col-4 {width: 33.33%;}"
        ".col-5 {width: 41.66%;}"
        ".col-6 {width: 50%;}"
        ".col-7 {width: 58.33%;}"
        ".col-8 {width: 66.66%;}"
        ".col-9 {width: 75%;}"
        ".col-10 {width: 83.33%;}"
        ".col-11 {width: 91.66%;}"
        ".col-12 {width: 100%;}"
        "}"
        "</style>"
        "</head>"
        "<body>"
        "<div class=\"header\">"
        "<h1>Dom&oacute;tica FaMeLi</h1>"
        "</div>"
        "<div class=\"row\">"
        "<div class=\"col-3 col-s-3 menu\">"
        "<div class=\"aside\">"
        "<h2>PROYECTO FINAL</h2>"
        //"<br>"
        "<h2><img src=\"\\ecea.png\" alt=\"logo\" width=\"95\" height=\"75\"></h2>"
        //"<br>"
        "<h2>6to ELECTR&Oacute;NICA</h2>"
        "</div>"
        "</div>"
        "<div class=\"col-6 col-s-9\">"
        "<div class=\"aside\">"
        "<h2>PANEL DE CONTROL</h2>"
        "<br>"
        "<h2>Temperatura recibida: %d&#176C </h2>"
        "<h2>Humedad recibida: %d\%</h2>"
        "<h2>Iluminaci&oacute;n recibida: %d LUX</h2>"
        "<form method = \"GET\" action=\"./pruebacgi.cgi\">"
        "<h2><button type=\"checkbox\" class=\"button_refresh\" name=\"Refresh\" value=\"Refresh\">Actualizar</h2>"
        "</div>"
        "</div>"
        "<div class=\"col-3 col-s-12\">"
        "<div class=\"aside\">"
        "<form method = \"GET\" action=\"./pruebacgi.cgi\">"
        "<h2>ELIJA QUE PRENDER O APAGAR</h2>"
        "<h2><button type=\"checkbox\" class=\"button_lamp\" name=\"luz\" value=\"Lampara\">L&aacute;mpara</h2>"
        "<h2><button type=\"checkbox\" class=\"button_vent\" name=\"aire\" value=\"Ventilador\">Ventilador</h2>"
        "</form>"
        "</div>"
        "</div>"
        "</div>"
        "<div class=\"footer\">"
        "<p>Queremos agradecer a Guillermo Ferrari, Nahuel Espinosa, Claudio Trabado y Leonardo Davico, por ser excelentes profesores "
        "y personas, a nuestras familias y a Valentina, Nahiara y Josefina, nuestras novias. Gracias por bancarnos y ayudarnos durante todo el a&ntilde;o.</p>"
        "</div>"
        "</body>"
        "</html>"
        ,color0,color1,aux[2],aux[5],lux16
    );
    return 0;
}
