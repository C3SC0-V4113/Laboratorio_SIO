/*Consumidor*/
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
    if ((shmid = shmget(KEY, SIZE * sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        perror("shmget");
        exit(2);
    }
    if ((adr = shmat(shmid, 0, 0)) == (int *)-1)
    {
        perror("shmat");
        exit(2);
    }
    srand(getpid());
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", adr[i]);
    }
    putchar("\n");
    return 0;
}