#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *hilo1(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("Mensaje Hilo #1\n");
        sleep(1);
    }
    return NULL;
}

void *hilo2(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("Mensaje Hilo #2\n");
        sleep(1);
    }
    return NULL;
}

void *hilo3(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("Mensaje Hilo #3\n");
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t mihilo_1;
    pthread_t mihilo_2;
    pthread_t mihilo_3;
    if (pthread_create(&mihilo_1, NULL, hilo1, NULL))
    {
        printf("error creando hilo");
        abort();
    }
    if (pthread_create(&mihilo_2, NULL, hilo2, NULL))
    {
        printf("error creando hilo");
        abort();
    }
    if (pthread_create(&mihilo_3, NULL, hilo3, NULL))
    {
        printf("error creando hilo");
        abort();
    }
    printf("Esperando finalización de Hilos\n");

    int i;
    for (i = 0; i < 10; i++)
    {
        printf("Mensaje Generado por Main\n");
        sleep(1);
    }

    if (pthread_join(mihilo_1, NULL))
    {
        printf("Error finalización Hilo 1");
        abort();
    }
    if (pthread_join(mihilo_2, NULL))
    {
        printf("Error finalización Hilo 2");
        abort();
    }
    if (pthread_join(mihilo_3, NULL))
    {
        printf("Error finalización Hilo 3");
        abort();
    }
    printf("Fin Ejecución de Hilos\n");
    exit(0);
}
