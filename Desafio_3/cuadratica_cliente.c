#include "cuadratica.h"

struct mensaje
{
    long tipo;
    double A;
    double B;
    double C;
};

struct respuesta
{
    int tipo;
    complex double X1;
    complex double X2;
};

int main(int argc, char *argv[])
{
    int id01, id02;
    unsigned int lenmsg;
    struct mensaje msgA;
    struct respuesta response;

    int sockfd, n;
    struct sockaddr_in dir_cli, dir_serv;
    char lineaenv[MAXLINEA], linearec[MAXLINEA];

    bzero((char *)&dir_serv, sizeof(dir_serv));

    dir_serv.sin_family = AF_INET;
    dir_serv.sin_addr.s_addr = inet_addr(argv[1]);
    dir_serv.sin_port = htons(PORT_UDP_SERV);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        error("Cliente: no se puede abrir socket");

    if (connect(sockfd, (struct sockaddr *)&dir_serv, sizeof(dir_serv)) < 0)
        error("cliente: error funcion connect");

    msgA.tipo = 1;
    printf("****Cliente****\n");
    printf("Para resolver una ecuacion cuadratica digite los siguientes datos\n");
    printf("Digite el valor de a: ");
    scanf("%lf", &msgA.A);
    printf("\nDigite el valor de b: ");
    scanf("%lf", &msgA.B);
    printf("\nDigite el valor de c: ");
    scanf("%lf", &msgA.C);

    if (write(sockfd, &msgA, 32) == -1)
        error("cliente: error funcion write");

    n = read(sockfd, &response, 32);

    if (n < 0)
        error("cliente: error funcion read");

    printf("\nResultado: \n");
    if (((int) response.tipo) == 0)
    {
        printf("Los resultados son: \nx1:%f \nx2:%f", creal(response.X1), creal(response.X2));
    }
    else
    {
        printf("Los resultado complejos son: \nx1: %.2lf+%.2lfi",creal(response.X1),cimag(response.X1));
        printf("\nx2: %.2lf+%.2lfi",creal(response.X2),cimag(response.X2));
    }
    printf("\n\n");

    close(sockfd);
    exit(0);
}
