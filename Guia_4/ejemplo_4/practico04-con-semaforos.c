#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char const *argv[])
{
    struct sembuf semvar;
    int semid;
    int i=0,j,pid;

    semid=semget(IPC_PRIVATE,1,IPC_CREAT|0600);
    semvar.sem_num=0;
    semvar.sem_flg=0;
    semctl(semid,0,SETVAL,1);

    pid=fork();

    if (pid==-1)
    {
        perror("fork");
        exit(-1);
    }
    if (pid==0)
    {
        semvar.sem_op=-1;
        semop(semid,&semvar,1);
        for ( j = 0; j < 100; j++)
        {
            write(STDOUT_FILENO,"o",1);
            sleep(1);
        }
        semvar.sem_op=1;
        semop(semid,&semvar,1);
    }
    else
    {
        semvar.sem_op=-1;
        semop(semid,&semvar,1);
        for ( j = 0; j < 100; j++)
        {
            write(STDOUT_FILENO,"+",1);
            sleep(1);
        }
        semvar.sem_op=1;
        semop(semid,&semvar,1);
    }
    semctl(semid,0,IPC_RMID,0);
}
