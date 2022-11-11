#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *funcion01(void *arg)
{
    //Función que permite repetir 100 veces el asterisco
    int i;
    for (i = 0; i < 100; i++)
    {
        printf("-");
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}

void *funcion02(void *arg)
{
    //Funcion que permite repetir 100 veces la letra o
    int i;
    for (i = 0; i < 100; i++)
    {
        printf("*");
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}

void *funcion03(void *arg)
{
    //Funcion que permite repetir 100 veces la letra o
    int i;
    for (i = 0; i < 100; i++)
    {
        printf("+");
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}

void *funcion04(void *arg)
{
    //Funcion que permite repetir 100 veces la letra o
    int i;
    for (i = 0; i < 100; i++)
    {
        printf("o");
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    int i;
    pthread_t h1, h2,h3,h4;
    //Se crean ambos hilos basandose en las funciones de repetición
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
    //Se lanza un hilo después del otro
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    pthread_join(h3, NULL);
    pthread_join(h4, NULL);
    printf("\n");
    return 0;
}
