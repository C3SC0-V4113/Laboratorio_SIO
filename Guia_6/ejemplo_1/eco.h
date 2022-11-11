#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define     PORT_TCP_SERV   6500
#define     PORT_TCP_CLI    6501
#define     MAXLINEA        100

#define error(mesg) { perror(mesg); exit(1); }