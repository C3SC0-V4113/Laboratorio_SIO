/* Consumidor Cola de Mensajes */
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

    if ((id01 = msgget(LLAVE, IPC_CREAT | 0600)) == -1)
    {
        perror("error msgget");
    }
    if (msgrcv(id01, &msg01, MAXIMO, 0, 0) == -1)
    {
        perror("msgrcv error");
    }
    lenmsg = strlen(msg01.texto);
    msg01.texto[lenmsg] = '\0';
    printf("\n%s\n%zu\n", msg01.texto, strlen(msg01.texto));

    if (msgrcv(id01, &msg01, MAXIMO, 0, 0) == -1)
    {
        perror("msgrcv error");
    }

    lenmsg = strlen(msg01.texto);
    msg01.texto[lenmsg] = '\0';
    printf("\n%s\n%zu\n", msg01.texto, strlen(msg01.texto));
}
