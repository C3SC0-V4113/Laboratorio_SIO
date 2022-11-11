#include "eco.h"

int main(int argc, char const *argv[])
{
    int sockfd, n, newsockfd, len_cli;
    struct sockaddr_in dir_cli, dir_serv;
    char linea[MAXLINEA];

    bzero((char*) &dir_serv, sizeof(dir_serv));

    dir_serv.sin_family=AF_INET;
    dir_serv.sin_addr.s_addr=htonl(INADDR_ANY);
    dir_serv.sin_port=htons(PORT_TCP_SERV);

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        error("Servidor: No se puede crear socket");
    }

    if (bind(sockfd,(struct sockaddr *) &dir_serv,sizeof(dir_serv))<0)
    {
        error("Servidor: No se puede asociar la direccion local");
    }
    listen(sockfd,5);

    for (  ;   ; )    {
        len_cli=sizeof(dir_cli);
        newsockfd=accept(sockfd,(struct sockaddr *)&dir_cli, &len_cli);

        if (newsockfd<0)
        {
            error("Servidor: error al aceptar la función")
        }
        
        while ((n=read(newsockfd,linea,MAXLINEA))!=0)
        {
            if (n<0)
            {
                error("Servidor: Error en la lectura");
            }
            
            if (n!=write(newsockfd,linea,n))
            {
                error("Servidor: Error al escribir");
            }
            
        }
        close(newsockfd);
    }
    
    
}
