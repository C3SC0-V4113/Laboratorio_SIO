#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define LLAVE 34856
#define MAXIMO 100

struct mensaje
{
    long tipo;
    char texto[MAXIMO];
};

int main()
{
    key_t llave01;
    int id01, i;
    unsigned int lenmsg;
    struct mensaje msg01;

    if ((id01=msgget(LLAVE,0600|IPC_CREAT))==-1)
    {
        perror("error msgget");
    }
    while (strcmp(msg01.texto, "salir\n"))
    {
        if (msgrcv(id01, &msg01,MAXIMO,0,0)==-1)
        {
            perror("error msgrcv");
        }
        lenmsg=strlen(msg01.texto);
        msg01.texto[MAXIMO]='\0';
        printf("\nrecibido: %s\n", msg01.texto);
    }
    if (msgctl(id01,IPC_RMID,NULL)==-1)
    {
        perror("error msgctl");
    }
    
}
