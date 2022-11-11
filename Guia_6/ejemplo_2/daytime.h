#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define     PORT_UDP_SERV   3480
#define     PORT_UDP_CLI    3481
#define     MAXLINEA        100

#define error(mesg) { perror(mesg); exit(1); }