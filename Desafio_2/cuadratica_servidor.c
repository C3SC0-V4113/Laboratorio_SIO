#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>

int main()
{
    int fd1,fdflag1, n;
    int a, b, c, flag;

    int buf[3];
    complex double total[2], x1, x2;
    float d;
    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";
    char *flagfifo= "/tmp/flagfifo";
    fd1 = open(mififo, O_RDONLY);
    fdflag1=open(flagfifo, O_RDONLY);
    read(fd1, buf, sizeof(buf));
    read(fdflag1, &flag, sizeof(flag));
    a = buf[0];
    b = buf[1];
    c = buf[2];
    // printf("a: %d, b: %d, c: %d", a, b, c);
    // Proceso de cuadratica
    d = (b * b - (4 * a * c));

    x1 = ((-b + csqrt(d)) / (2 * a));
    x2 = ((-b - csqrt(d)) / (2 * a));
    total[0] = x1;
    total[1] = x2;
    close(fd1);
    close(fdflag1);

    // Abriendo la FIFO para escribir el resultado
    if (d < 0)
    {
        flag = 1;
    }
    fd1 = open(mififo, O_WRONLY);
    fdflag1=open(flagfifo, O_WRONLY);
    write(fdflag1, &flag, sizeof(flag));
    write(fd1, total, sizeof(total));
    close(fd1);
    close(fdflag1);
    return 0;
}
