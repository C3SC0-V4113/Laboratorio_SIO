#include "daytime.h"

int main(int argc, char const *argv[])
{
    int sockfd,n,len_cli;
    struct sockaddr_in dir_cli,dir_serv;
    char buffer[MAXLINEA];
    time_t ticks;

    bzero((char*) &dir_serv,sizeof(dir_serv));

    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        error("Servidor: No se puede crear el socket");
    }

            dir_serv.sin_family=AF_INET;
    dir_serv.sin_addr.s_addr=INADDR_ANY;
    dir_serv.sin_port=htons(PORT_UDP_SERV);
    
    if (bind(sockfd,(struct sockaddr*)&dir_serv,sizeof(dir_serv))<0)
    {
        error("Servidor: No se puede asociar a la dirección local");
    }
    
    for ( ; ;)
    {
        len_cli=sizeof(dir_cli);
        n=recvfrom(sockfd,buffer,MAXLINEA,0,(struct sockaddr*)&dir_cli,&len_cli);
        ticks=time(NULL);
        snprintf(buffer,sizeof(buffer),"%s\r\n",ctime(&ticks));
        if (sendto(sockfd,buffer,sizeof(buffer),0, (struct sockaddr*)&dir_cli,sizeof(dir_cli))<0)
        {
            error("Servidor: error funcion de enviar");
        }
        
    }
    
}
