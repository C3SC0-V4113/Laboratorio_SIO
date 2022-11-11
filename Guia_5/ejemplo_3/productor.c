/*Productor*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#define SIZE 64
#define KEY (key_t)1000

int main(int argc, char const *argv[])
{
    int shmid;
    int *adr;
    int i;
    //se crea el objeto de memoria compartido
    if ((shmid = shmget(KEY, SIZE * sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        perror("shmget");
        exit(2);
    }
    //Se enlaza el objeto en memoria con un puntero de números
    if ((adr = shmat(shmid, 0, 0)) == (int *)-1)
    {
        perror("shmat");
        exit(2);
    }
    //Se inicializa el escritor de números aleatorios
    srand(getpid());
    for (i = 0; i < SIZE; i++)
    {
        //Se imprime y se guarda el número aleatorio en memoria
        printf("%d ", adr[i] = rand() % 100);
    }
    putchar("\n");
    return 0;
}
