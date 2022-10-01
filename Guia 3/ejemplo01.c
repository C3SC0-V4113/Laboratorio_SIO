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

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
