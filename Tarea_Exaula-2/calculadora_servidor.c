#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <regex.h>

int main()
{
    int fd1;
    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";
    // Creación de Expresiones Regulares
    regex_t regexSymbols;

    // Crear archivo FIFO
    // mkfifo(mififo, 0666);
    char str1[80], str2[80],retorno[80],searcher[80];
    // Banderas, numero de for y longuitud para el calculo
    int i, lenght, lword;
    int flag = 0;
    while (1)
    {
        // Abrir FIFO en solo lectura
        fd1 = open(mififo, O_RDONLY);
        read(fd1, str1, 80);

        // Imprimir el string y procesarlo
        printf("PROCESANDO SOLICITUD\n");
        printf("Antes de procesar: %s",str1);
        strcpy(searcher,"+");
        strcpy(retorno,strstr(str1,searcher));
        printf("Retorno: %s",retorno);
        char * token = strtok(str1,searcher);
        int suma=0;
        while (token!=NULL)
        {
            suma+=((int)token-48);

        }
        printf("La suma es %d",suma);
        
        /*lenght = strlen(str1);
        for (i = 1; i < lenght; i++)
        {
            lword = lenght - 1 - i;
            if (str1[i - 1] != str1[lword])
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            strcpy(str2, "No es palindroma");
            flag = 0;
        }
        else
        {
            strcpy(str2, "Si es palindroma");
        }*/
        close(fd1);

        // Abriendo la FIFO para escribir el resultado
        fd1 = open(mififo, O_WRONLY);
        write(fd1, str2, strlen(str2) + 1);
        close(fd1);
    }

    return 0;
}
