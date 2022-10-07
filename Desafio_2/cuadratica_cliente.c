#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <complex.h>

int main()
{
    int fd,fdflag;
    int a, b, c, flag = 0;

    int buf[3];
    complex double total[2];
    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";
    char *flagfifo= "/tmp/flagfifo";

    // Crear archivo FIFO
    mkfifo(mififo, 0666);
    mkfifo(flagfifo,0666);

    printf("*** Bienvenido a la calculadora de Cuadraticas ***\n");
    fd = open(mififo, O_WRONLY);
    fdflag=open(flagfifo, O_WRONLY);

    // Entrada de Datos
    printf("*** Digite los datos de entrada ***");
    printf("\nDigite el primer número: ");
    scanf("%i", &a);
    printf("\nDigite el segundo número: ");
    scanf("%i", &b);
    printf("\nDigite el tercer número: ");
    scanf("%i", &c);

    // Convirtiendo en un array
    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    // Escribe el input en la FIFO y lo cierra
    write(fd, buf, sizeof(buf));
    close(fd);
    write(fdflag, &flag, sizeof(flag));
    close(fdflag);

    // Abrir FIFO en solo lectura
    fd = open(mififo, O_RDONLY);
    fdflag=open(flagfifo, O_RDONLY);
    // Leer FIFO
    read(fd, total, sizeof(total));
    read(fdflag, &flag, sizeof(flag));

    // Leer el mensaje
    printf("flag: %d\n", flag);
    if (flag == 0)
    {
        printf("Los resultados son: \nx1:%f \nx2:%f", creal(total[0]), creal(total[1]));
    }
    else
    {
        printf("Los resultado complejos son: \nx1: %.2lf+%.2lfi",creal(total[0]),cimag(total[0]));
        printf("\nx2: %.2lf+%.2lfi",creal(total[1]),cimag(total[1]));
    }

    printf("\n\n");
    close(fd);
    close(fdflag);

    return 0;
}
