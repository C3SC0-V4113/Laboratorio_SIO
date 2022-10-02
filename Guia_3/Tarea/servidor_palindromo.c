#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd1;
    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";

    // Crear archivo FIFO
    mkfifo(mififo, 0666);
    char str1[80], str2[80];
    // Banderas, numero de for y longuitud para el calculo
    int i, lenght,lword;
    int flag = 0;
    while (1)
    {
        // Abrir FIFO en solo lectura
        fd1 = open(mififo, O_RDONLY);
        read(fd1, str1, 80);

        // Imprimir el string y procesarlo
        printf("La palabra es: %s\n", str1);
        lenght = strlen(str1);
        for (i = 1; i < lenght; i++)
        {
            lword=lenght-1-i;
            printf("Posiciones finales %d\n",lword);
            printf("Primera Letra %d\n", str1[i-1]);
            printf("Ultima Letra %d\n", str1[lword]);
            if (str1[i-1] != str1[lword])
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            strcpy(str2, "No es palindroma");
        }
        else
        {
            strcpy(str2, "Si es palindroma");
        }
        printf("aver: %s\n", str2);
        close(fd1);
    }

    // Abriendo la FIFO para escribir el resultado
    fd1 = open(mififo, O_WRONLY);
    write(fd1, str2, strlen(str2) + 1);
    close(fd1);

    return 0;
}
