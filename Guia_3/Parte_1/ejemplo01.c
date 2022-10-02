#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *hilo1(void *arg)
{
    int i;
    for ( i = 0; i < 10; i++)
    {
        printf("Mensaje Generado por Hilo1\n");
    }
    return(NULL);
}

int main(void)
{
    pthread_t mihilo;
    int i;

    printf("Esperando finalización de hilos\n");

    if (pthread_create(&mihilo,NULL,hilo1,NULL))
    {
        printf("Error creando el Hilo 1");
        abort();
    }
    for ( i = 0; i < 10; i++)
    {
        printf("Mensaje Generado por Main\n");
    }
    if (pthread_join(mihilo,NULL))
    {   
        printf("Error esperando finalización de hilos.");
        abort();
    }
    printf("Fin ejecución de hilos\n");
    exit(0);
}
