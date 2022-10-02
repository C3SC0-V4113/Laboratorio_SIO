#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char mensaje[100], *nfifo="fifo";
    int fd;
    printf("***  Consumidor  ***\n");
    fd=open(nfifo, O_RDONLY);
    if (fd==-1)
    {
        perror("Error al abror la tuberia (lectura)\n");
    }
    else
    {
        read(fd,mensaje,100);
        printf("Consumidor recibo mensaje: %s\n",mensaje);
        close(fd);
    }
    unlink(nfifo);
}
