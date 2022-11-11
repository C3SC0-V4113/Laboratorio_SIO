#include "daytime.h"

int main(int argc, char const *argv[])
{
    int sockfd,n;
    struct sockaddr_in dir_cli, dir_serv;
    char buffer[MAXLINEA]="0";

    bzero((char*) &dir_cli,sizeof(dir_cli));

    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
    {
        error("Cliente: No se puede abrir el socket");
    }

    dir_cli.sin_family=AF_INET;
    dir_cli.sin_addr.s_addr=INADDR_ANY;
    dir_cli.sin_port=htons(PORT_UDP_CLI);

    if (bind(sockfd,(struct sockaddr*)&dir_cli,sizeof(dir_cli))==-1)
    {
        error("Cliente: No se puede asociar la dirección local");
    }

    bzero((char*)&dir_serv,sizeof(dir_serv));

    dir_serv.sin_family=AF_INET;
    dir_serv.sin_addr.s_addr=INADDR_ANY;
    dir_serv.sin_port=htons(PORT_UDP_SERV);
        if (argc>2)
    {
        dir_serv.sin_addr.s_addr=inet_addr(argv[1]);
    }

    if (sendto(sockfd,buffer,MAXLINEA,0,(struct sockaddr*)&dir_serv,sizeof(dir_serv))==-1)
    {
        error("Cliente: Error al enviar");
    }
    
    n=recvfrom(sockfd,buffer,MAXLINEA,0, (struct sockaddr*)0,(int*)0);

    if (n<0)
    {
        error("Cliente: Error al recibir");
    }
    
    buffer[n]=0;
    fputs(buffer,stdout);

    close(sockfd);
    exit(0);
}
