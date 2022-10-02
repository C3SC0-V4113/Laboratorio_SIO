#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LEER 0
#define ESCRIBIR 1

int main()
{
    int descr[2];
    int bytesleidos;
    char mensaje[100],*frase="Que facil es Sistemas Opertivos, sobre todo el uso de Tuberias";
    printf("**** Ejemplo de comunicación entre procesos emparentados. ****\n");
    pipe(descr);
    if (fork()==0) 
    {
        close(descr[LEER]);
        write(descr[ESCRIBIR],frase,strlen(frase));
        close(descr[ESCRIBIR]);
    }
    else
    {
        close(descr[ESCRIBIR]);
        bytesleidos=read(descr[LEER],mensaje,100);
        mensaje[bytesleidos]='\0';
        printf("Bytes leidos: %d\n",bytesleidos);
        printf("Mensaje recibido por el Proceso Padre: %s\n",mensaje);
        close(descr[LEER]);
    }    
}


