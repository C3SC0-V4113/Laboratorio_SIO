#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int i=0,j,pid;

    pid=fork();

    if (pid==-1)
    {
        perror("fork");
        exit(-1);
    }
    if (pid==0)
    {
        for ( j = 0; j < 100; j++)
        {
            write(STDOUT_FILENO, "o",1);
            sleep(1);
        }
        
    }
    else{
        for ( j = 0; j < 100; j++)
        {
            write(STDOUT_FILENO,"+",1);
            sleep(1);
        }
        
    }

}
