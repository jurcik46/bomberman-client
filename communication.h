

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
#include "Menu/menu.h"

#include "constants.h"

#define BUFFER_SIZE 1024
#define NAME_LENGTH 50

typedef struct socket {
    int sock;
    char buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
} Socket;


extern enum result_code communication(enum communication_type commuType, char *data);

enum result_code loginToServer(char *data);

enum result_code createGameToServer(char *data);

void getPlayerInLobby(char *data);

void findGameFromServer(char *data);

enum result_code joinLobbyToServer(char *data);

void leaveLobby(char *data);

enum result_code resultFromRequest();

void downloadMapFromServer(char * data);

char *dataFromRequest();

void initSocket(char *ipAddress, u_int16_t port);

_Bool socketReady();


void closeSocket();

#endif //BOMBERMAN_CLIENT_COMMUNICATION_H
