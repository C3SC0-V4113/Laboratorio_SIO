#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd, n;
    int a, b, c;

    int buf[3];
    float total[2];
    // Dirección del archivo FIFO
    char *mififo = "/tmp/mififo";

    // Crear archivo FIFO
    mkfifo(mififo, 0666);

    printf("*** Bienvenido a la calculadora de Cuadraticas ***\n");
    fd = open(mififo, O_WRONLY);

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

    // Abrir FIFO en solo lectura
    fd = open(mififo, O_RDONLY);
    // Leer FIFO
    read(fd, total, sizeof(total));

    // Leer el mensaje
    printf("Los resultados son: %f y %f", total[0], total[1]);
    printf("\n\n");
    close(fd);

    return 0;
}
