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
        printf("o");
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
    pthread_t h1, h2;
    //Iniciar Hilo Mutex
    pthread_mutex_init(&varmutex, NULL);
    //Creación de ambos hilos en las variables
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
    //Llamar a ambos hilos hasta que terminen ambos
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    //Destruir Mutex
    pthread_mutex_destroy(&varmutex);
    printf("\n");
    return 0;
}
