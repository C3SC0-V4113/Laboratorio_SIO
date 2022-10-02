#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;

    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";

    // Crear archivo FIFO
    mkfifo(mififo, 0666);
    char arr1[80], arr2[80];
    while (1)
    {
        // Abrir la FIFO solo para escribir
        fd = open(mififo, O_WRONLY);
        // Obtiene un input del usuario de longuitud máxima de 80
        fgets(arr2, 80, stdin);
        // Escribe el input en la FIFO y lo cierra
        write(fd, arr2, strlen(arr2) + 1);
        close(fd);

        // Abrir FIFO en solo lectura
        fd = open(mififo, O_RDONLY);
        // Leer FIFO
        read(fd, arr1, sizeof(arr1));

        // Leer el mensaje
        printf("Aver: %s\n", arr1);
        close(fd);
    }
    return 0;
}
