#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int i,fd,contador=0;
    char caracter;
    char *org, *p;
    struct stat bstat;

    if (argc!=3)
    {
        fprintf(stderr, "Uso: %s caracter archivo\n",argv[0]);
        return(1);
    }

    caracter=argv[1][0];
    if ((fd=open(argv[2], O_RDONLY))<0)
    {
        perror("No puede abrirse el archivo");
        return(1);
    }

    if (fstat(fd,&bstat)<0)
    {
        perror("Error en fstat del archivo");
        close(fd);
        return(1);
    }

    if ((org=mmap((caddr_t)0,bstat.st_size,PROT_READ,MAP_SHARED,fd,0))==MAP_FAILED)
    {
        perror("Error en la proyección del archivo");
        close(fd);
        return(1);
    }

    close(fd);
    
    p=org;
    for ( i = 0; i < bstat.st_size; i++)
    {
        if (*p++==caracter)
        {
            contador++;
        }

    }
    munmap(org,bstat.st_size);

    printf("%d\n",contador);    
    
    return 0;
}
