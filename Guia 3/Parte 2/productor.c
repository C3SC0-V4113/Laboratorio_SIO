#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int bandera, fd;
    char *nfifo = "fifo";
    printf("***  Productor  ***\n");
    if (argc != 2)
    {
        fprintf(stderr, "modo de uso: ./productor mensaje \n");
        exit(1);
    }
    bandera = mkfifo(nfifo, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if (!bandera)
    {
        printf("Productor espera apertura de consumidor\n");
        fd = open(nfifo, O_WRONLY);
        if (fd == -1)
        {
            perror("Error al abrir la tuberia (escritura)\n");
        }
        else
        {
            write(fd, argv[1], 100);
            printf("Productor envio mensaje: %s\n", argv[1]);
            close(fd);
        }
    }
    else
    {
        perror("Error al crear la tuberia\n");
    }
    return 0;
}
