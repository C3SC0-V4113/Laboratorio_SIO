#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd, flag = 0;

    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";

    // Crear archivo FIFO
    mkfifo(mififo, 0666);
    char arr1[80], arr2[80];
    printf("**** Calculadora básica ****\n");
    printf("**** Pulse 'q' para salir ****\n");
    do
    {
        // Abrir la FIFO solo para escribir
        fd = open(mififo, O_WRONLY);
        // Obtiene un input del usuario de longuitud máxima de 80
        printf("Ingrese la operación: ");
        fgets(arr2, 80, stdin);
        // Revisa que se pulse q para salirse
        if (*arr2 == 'q')
        {
            flag = 1;
        }
        else
        {
            // Escribe el input en la FIFO y lo cierra
            write(fd, arr2, strlen(arr2) + 1);
            close(fd);

            // Abrir FIFO en solo lectura
            fd = open(mififo, O_RDONLY);
            // Leer FIFO
            read(fd, arr1, sizeof(arr1));

            // Leer el mensaje
            printf("%s", arr1);
            printf("\n\n");
            close(fd);
        }
    } while (flag == 0);
    printf("¡Programa Terminado!\n");
    return 0;
}
