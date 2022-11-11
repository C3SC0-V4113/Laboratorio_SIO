#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t varmutex;

void *funcion01(void *arg)
{
    int i;
    //Desbloquear hilo Mutex
    pthread_mutex_lock(&varmutex);
    for (i = 0; i < 100; i++)
    {
        printf("*");
        fflush(stdout);
        sleep(1);
    }
    //Bloquear hilo Mutex
    pthread_mutex_unlock(&varmutex);
    return NULL;
}

void *funcion02(void *arg)
{
    int i;
    //Desbloquear Hilo Mutex
    pthread_mutex_lock(&varmutex);
    for (i = 0; i < 100; i++)
    {
        printf("+");
        fflush(stdout);
        sleep(1);
    }
    //Bloquear Hilo Mutex
    pthread_mutex_unlock(&varmutex);
    return NULL;
}

void *funcion03(void *arg)
{
    int i;
    //Desbloquear Hilo Mutex
    pthread_mutex_lock(&varmutex);
    for (i = 0; i < 100; i++)
    {
        printf("o");
        fflush(stdout);
        sleep(1);
    }
    //Bloquear Hilo Mutex
    pthread_mutex_unlock(&varmutex);
    return NULL;
}

void *funcion04(void *arg)
{
    int i;
    //Desbloquear Hilo Mutex
    pthread_mutex_lock(&varmutex);
    for (i = 0; i < 100; i++)
    {
        printf("-");
        fflush(stdout);
        sleep(1);
    }
    //Bloquear Hilo Mutex
    pthread_mutex_unlock(&varmutex);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int i;
    pthread_t h1, h2, h3, h4;
    //Iniciar Hilo Mutex
    pthread_mutex_init(&varmutex, NULL);
    //Creación de los 4 hilos en las variables
    if (pthread_create(&h1, NULL, funcion01, NULL))
    {
        printf("error creando hilo 1");
        abort();
    }
    if (pthread_create(&h2, NULL, funcion02, NULL))
    {
        printf("error creando hilo 2");
        abort();
    }
        if (pthread_create(&h3, NULL, funcion03, NULL))
    {
        printf("error creando hilo 3");
        abort();
    }
        if (pthread_create(&h4, NULL, funcion04, NULL))
    {
        printf("error creando hilo 4");
        abort();
    }
    //Llamar a los 4 hilos hasta que terminen todos
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    pthread_join(h3, NULL);
    pthread_join(h4, NULL);
    //Destruir Mutex
    pthread_mutex_destroy(&varmutex);
    printf("\n");
    return 0;
}
