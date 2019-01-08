

#ifndef BOMBERMAN_CLIENT_COMMUNICATION_H
#define BOMBERMAN_CLIENT_COMMUNICATION_H

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>

#include "logging/log.h"
#include "constants.h"

#define BUFFER_SIZE 1024
#define NAME_LENGTH 50

typedef struct socket {
    int sock;
    int stop;

    char buffer[BUFFER_SIZE];
    _Bool end;
    pthread_mutex_t mutex;
} Socket;

pthread_t socketThread;
/**
 * Communication Select
 */
fd_set socketDs;
int sd;
int activity;

struct sockaddr_in address;
struct sockaddr_in serv_addr;

Socket sock;

enum result_code communication(enum communication_type commuType, char *data);

enum result_code loginToServer(char *data);

enum result_code createGameToServer(char *data);

void findGameFromServer(char *data);

enum result_code joinLobbyToServer(char *data);

enum result_code resultFromRequest();

char *dataFromRequest();

void initSocket(char *ipAddress, u_int16_t port);

_Bool socketReady();

void initThreadSocket();

void closeSocket();

#endif //BOMBERMAN_CLIENT_COMMUNICATION_H
