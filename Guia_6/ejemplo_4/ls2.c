#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <error.h>

#define SIZE_ALM 1024

void main(int argc, char const *argv[])
{
    DIR *dirp;
    struct dirent *dp;
    char almacen[SIZE_ALM];

    if (argc<2)
    {
        fprintf(stderr,"Uso: ls2 directorio\n");
        exit(1);
    }

    getcwd(almacen,SIZE_ALM);
    printf("Directorio actual: %s\n",almacen);

    dirp=opendir(argv[1]);
    if (dirp==NULL)
    {
        fprintf(stderr, "No se pudo abrir el directorio:  %s\n",argv[1]);
        exit(1);
    }else
    {
        printf("Entradas en el directorio: %s \n",argv[1]);
        while ((dp=readdir(dirp))!=NULL)
            printf("%s\n", dp->d_name);
        closedir(dirp);
    }
    exit(0);
}
