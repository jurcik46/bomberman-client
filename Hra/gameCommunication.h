//
// Created by jurci on 9. 1. 2019.
//

#ifndef BOMBERMAN_CLIENT_GAMECOMMUNICATION_H
#define BOMBERMAN_CLIENT_GAMECOMMUNICATION_H

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
#include "gameConstants.h"
#include "../logging/log.h"
#include "../Menu/menu.h"
#include "../communication.h"
#include "../constants.h"

#define BUFF_SIZE 100

typedef struct gameSocket {
    int sock;
    char buffer[BUFF_SIZE];
//    pthread_mutex_t mutex;
} GameSocket;


void initGameSocket(char *ipAddress, u_int16_t port, Game g );

enum gameEnum gameCommunication(enum gameEnum commuType, char *data);

void closeSocketGame();

_Bool socketReadyGame();

#endif //BOMBERMAN_CLIENT_GAMECOMMUNICATION_H
