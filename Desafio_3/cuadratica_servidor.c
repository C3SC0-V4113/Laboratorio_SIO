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

int main()
{

    double d, e, f, X1, X2;
    int id01, id02;
    unsigned int lenmsg;

    // struct mensaje msg01;
    struct mensaje msgA;
    struct respuesta response;

    int sockfd, n, newsockfd, len_cli;
    struct sockaddr_in dir_cli, dir_serv;
    char linea[MAXLINEA];

    bzero((char *)&dir_serv, sizeof(dir_serv));

    dir_serv.sin_family = AF_INET;
    dir_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    dir_serv.sin_port = htons(PORT_UDP_SERV);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("servidor: no se puede crear socket");

    if (bind(sockfd, (struct sockaddr *)&dir_serv, sizeof(dir_serv)) < 0)
        error("servidor: no se puede asociar la dir local");

    listen(sockfd, 5);

    for (;;)
    {
        len_cli = sizeof(dir_cli);
        newsockfd = accept(sockfd, (struct sockaddr *)&dir_cli, &len_cli);

        if (newsockfd < 0)
            error("servidor: error funcion accept");

        while ((n = read(newsockfd, &msgA, 32)) != 0)
        {
            if (n < 0)
                error("servidor: error funcion read");

            printf("\n %lf, %lf, %lf \n", msgA.A, msgA.B, msgA.C);

            // Procedimiento

            d = (msgA.B * msgA.B - 4 * msgA.A * msgA.C);

            response.tipo = 0;
            if (((int)d) < 0)
            {

                e = (-msgA.B) / (2 * msgA.A);
                f = sqrt((-d)) / (2 * msgA.A);

                response.X1 = e;
                response.X2 = f;
                response.tipo = 1;
                // printf("\nEntrando a d<0");
            }

            if (((int)d) == 0)
            {
                X1 = (-msgA.B) / (2 * msgA.A);

                // printf("\nx1 = x2 = %lf",X1);

                response.X1 = X1;
                response.X2 = X1;
            }

            if (((int)d) > 0)
            {
                X1 = ((-msgA.B) + sqrt(d)) / (2 * msgA.A);
                X2 = ((-msgA.B) - sqrt(d)) / (2 * msgA.A);
                // printf("\nx1= %lf",X1);
                // printf("\nx2= %lf",X2);
                response.X1 = X1;
                response.X2 = X2;
            }

            if (n != write(newsockfd, &response, 32))
                error("servidor: error funcion write");
        }
        close(newsockfd);
    }
}
