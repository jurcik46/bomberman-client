

#ifndef BOMBERMAN_CLIENT_COMMUNICATION_H
#define BOMBERMAN_CLIENT_COMMUNICATION_H

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "logging/log.h"
#include "constants.h"

#define BUFFER_SIZE 1024


struct sockaddr_in address;
int sock;
struct sockaddr_in serv_addr;
char buffer[BUFFER_SIZE];


enum result_code communication(enum communication_type commuType, char *data);

enum result_code loginToServer(char *data);

void initSocket(char *ipAddress, u_int16_t port);

void closeSocket();

#endif //BOMBERMAN_CLIENT_COMMUNICATION_H
