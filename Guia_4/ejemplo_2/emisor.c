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
    int id01;
    unsigned int lenmsg;

    struct mensaje msg01;
    msg01.tipo = 1;
    printf("**** Emisor de mensajes, digitalizar \"salir\" para terminar el programa ****");

    while (strcmp(msg01.texto, "salir\n"))
    {
        printf("\nIngrese su mensaje entre comillas dobles "
               " (max 100 caracteres):");
        fflush(stdin);
        fgets(msg01.texto, MAXIMO, stdin);
        lenmsg = strlen(msg01.texto);

        if ((id01 = msgget(LLAVE, 0600 | IPC_CREAT)) == -1)
        {
            perror("error msgget");
        }
        if ((msgsnd(id01, &msg01, (lenmsg + 1), 0) == -1))
        {
            perror("error msgsnd");
        }
    }
}
