/* Productor Cola de Mensajes */
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

    struct mensaje msg01 =
        {
            1, "Que facil es Cola de Mensajes"};
    lenmsg = strlen(msg01.texto);

    if ((id01 = msgget(LLAVE, 0600 | IPC_CREAT)) == -1)
    {
        perror("error msgget");
    }

    if (msgsnd(id01, &msg01, lenmsg, 0) == -1)
    {
        perror("msgsnd error");
    }

    strcpy(msg01.texto, "Que facil y divertido es la asignatura Sistemas Operativos!!");

    lenmsg = strlen(msg01.texto);
    if (msgsnd(id01, &msg01, lenmsg, 0) == -1)
    {
        perror("msgsnd error");
    }
}
