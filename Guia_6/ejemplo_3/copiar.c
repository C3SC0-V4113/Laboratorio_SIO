#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_ALM 1024
int main(int argc, char const *argv[])
{
    int     fd_ent,fd_sal;
    char    almacen[SIZE_ALM];
    int     n_read;

    if (argc!=3)
    {
        fprintf(stderr,"Uso: copiar origen destino\n");
        exit(-1);
    }

    fd_ent=open(argv[1],O_RDONLY);
    if (fd_ent<0)
    {
        perror("open");
        exit(-1);
    }
    
    fd_sal=creat(argv[2],0644);
    if (fd_sal<0)
    {
        perror("creat");
        exit(-1);
    }
    
    if (flock(fd_ent,LOCK_SH)==-1)
    {
        perror("flock origen");
        close(fd_ent);
        close(fd_sal);
        exit(-1);
    }

    if (flock(fd_sal,LOCK_EX)==-1)
    {
        perror("flock destino");
        flock(fd_ent,LOCK_UN);
        close(fd_ent);
        close(fd_sal);
        exit(-1);
    }
    
    while ((n_read=read(fd_ent,almacen,SIZE_ALM))>0)
    {
        if (write(fd_sal,almacen,n_read)<n_read)
        {
            perror("write");
                    close(fd_ent);
        close(fd_sal);
        exit(-1);
        }
        
    }

    if (n_read<0)
    {
        perror("read");
        close(fd_ent);
        close(fd_sal);
        exit(-1);
    }
    flock(fd_ent,LOCK_UN);
    flock(fd_sal,LOCK_UN);

    close(fd_ent);
        close(fd_sal);
        exit(0);
    
}
