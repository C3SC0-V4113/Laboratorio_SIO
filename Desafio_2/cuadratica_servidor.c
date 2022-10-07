#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd1, n;
    int a, b, c;

    int buf[3];
    float total[2];
    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";
    fd1 = open(mififo, O_RDONLY);
    read(fd1, buf, sizeof(buf));

    a = buf[0];
    b = buf[1];
    c = buf[2];
    //printf("a: %d, b: %d, c: %d", a, b, c);
    //Proceso de cuadratica
    total[0] = b + c;
    total[1] = c - a;
    close(fd1);

    // Abriendo la FIFO para escribir el resultado
    fd1 = open(mififo, O_WRONLY);
    write(fd1, total, sizeof(total));
    close(fd1);
    return 0;
}
