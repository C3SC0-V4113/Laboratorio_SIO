#include "eco.h"

int main(int argc, char *argv[])
{
    int sockfd,n;
    struct sockaddr_in dir_cli, dir_serv;
    char lineaenv[MAXLINEA], linearec[MAXLINEA];

    bzero((char*) &dir_serv, sizeof(dir_serv));

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        error("cliente: no se puede abrir el socket");
    }

        dir_serv.sin_family=AF_INET;
    dir_serv.sin_addr.s_addr=INADDR_ANY;
    dir_serv.sin_port=htons(PORT_TCP_SERV);

    if (argc>2)
    {
        dir_serv.sin_addr.s_addr=inet_addr(argv[1]);
    }
    

    if (connect(sockfd, (struct sockaddr *)&dir_serv, sizeof(dir_serv)) < 0)
    {
        error("cliente: error al conectarse");
    }

    while ((fgets(lineaenv, MAXLINEA,stdin)!=NULL) && (strlen(lineaenv)!=1))
    {
        n=strlen(lineaenv);
        
        if (write(sockfd,lineaenv,strlen(lineaenv))==-1)
        {
            error("cliente: error al escribir")
        }

        n=read(sockfd,linearec, sizeof(linearec));

        if (n<0)
        {
            error("cliente: error al leer");
        }
        
        linearec[n]=0;

        fputs(linearec,stdout);
    }
    close(sockfd);
    exit(0);
}
