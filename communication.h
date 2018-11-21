

#ifndef BOMBERMAN_CLIENT_COMMUNICATION_H
#define BOMBERMAN_CLIENT_COMMUNICATION_H

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "logging/log.h"

#define BUFFER_SIZE 1024


struct sockaddr_in address;
int sock;
struct sockaddr_in serv_addr;
char buffer[BUFFER_SIZE];

void initSocket(char *ipAddress, u_int16_t port);

void closeSocket();

#endif //BOMBERMAN_CLIENT_COMMUNICATION_H
