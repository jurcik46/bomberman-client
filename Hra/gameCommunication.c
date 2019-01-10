//
// Created by jurci on 9. 1. 2019.
//

#include "gameCommunication.h"

GameSocket gameSocket;
Game *gameP;
fd_set socketDs;
int sd;
int activity;

struct sockaddr_in serv_addr;

void initGameSocket(char *ipAddress, u_int16_t port, Game *g) {
    gameSocket.sock = 0;
    gameP = g;
    bzero(&serv_addr, sizeof(serv_addr));

    if ((gameSocket.sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = inet_addr(ipAddress);
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;

//    gameSocket.sock = socket(AF_INET, SOCK_DGRAM, 0);


    if (inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr) <= 0) {
        log_error("Invalid address/ Address not supported ");
        printf("Adresa Game servera nie je dostupna! Adresa servera neexistuje! \n");
        sleep(1);
        exit(EXIT_FAILURE);
    }

    // connect to server
    if (connect(gameSocket.sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        log_error("Connection to Game server Failed  ");
        printf("Nepodarilo sa pripojit na Game server! Skontrolujte pripojenie. \n");
        sleep(1);
        exit(EXIT_FAILURE);
    }

    sd = gameSocket.sock;
    int myIndex = -1;
    for (int i = 0; i < gameP->pocetHracov; ++i) {
        if (gameP->users[i].amI) {
            myIndex = i;
        }

    }

    sprintf(gameSocket.buffer, "%d %d %s %d",
            IN_GAME,
            gameP->users[myIndex].id,
            gameP->users[myIndex].name,
            gameP->admin);

    sendto(gameSocket.sock, gameSocket.buffer, BUFFER_SIZE, 0, (struct sockaddr *) NULL, sizeof(serv_addr));
    log_debug("SLEEEEEEP SKONTROLUJ zbytok");
    sleep(10);
    // waiting for response
//    recvfrom(gameSocket.sock, gameSocket.buffer, sizeof(gameSocket.buffer), 0, (struct sockaddr *) NULL, NULL);
}

_Bool socketReadyGame() {
    FD_ZERO(&socketDs);
    FD_SET(sd, &socketDs);
    struct timeval tv;
    tv.tv_usec = 1;

    activity = select(sd + 1, &socketDs, NULL, NULL, &tv);

    if ((activity < 0) && (errno != EINTR)) {
        log_error("Select Socket Activity error");
    }
    if (sd != 0 && FD_ISSET(sd, &socketDs)) {
        if (recv(gameSocket.sock, gameSocket.buffer, BUFFER_SIZE, 0) == 0) {

            log_fatal("Server disconnected");
            //Close the socket and mark as 0 in list for reuse
            closeSocketGame();
            sleep(10);
            exit(EXIT_FAILURE);
        } else {
//            log_debug("data %s", sock.buffer);
            return true;
        }
    }

    return false;
}

void closeSocketGame() {
    close(gameSocket.sock);
    gameSocket.sock = 0;
}