//
// Created by jurci on 9. 1. 2019.
//

#include "gameCommunication.h"

GameSocket gameSocket;
//Game *gameP;
fd_set socketDsGame;
int sdGame;
int activityGame;

struct sockaddr_in serv_addr;

void initGameSocket(char *ipAddress, u_int16_t port, Game g, int myIndex) {
    gameSocket.sock = 0;
    Game gameP = g;
    bzero(&serv_addr, sizeof(serv_addr));

    if ((gameSocket.sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }
    if (inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr.s_addr) <= 0) {
        log_error("Invalid address/ Address not supported ");
        printf("Adresa Game servera nie je dostupna! Adresa servera neexistuje! \n");
        sleep(1);
        exit(EXIT_FAILURE);
    }

    log_debug("%s  %d", ipAddress, port);
    serv_addr.sin_addr.s_addr = inet_addr(ipAddress);
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;

    // connect to server
    if (connect(gameSocket.sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        log_error("Connection to Game server Failed  ");
        printf("Nepodarilo sa pripojit na Game server! Skontrolujte pripojenie. \n");
        sleep(1);
        exit(EXIT_FAILURE);
    }

    sdGame = gameSocket.sock;

    log_debug("HRAC PRVY    %s  Id  %d   bool %d", gameP.users[0].name, gameP.users[0].id, gameP.users[0].amI);
    log_debug("HRAC DRUHY    %s  Id  %d   bool %d", gameP.users[1].name, gameP.users[1].id, gameP.users[1].amI);

//    for (int i = 0; i < gameP.pocetHracov; ++i) {
//        if (gameP.users[i].amI) {
////            log_debug("som ja podmienka %d", i);
////            myIndex = i;
////        }
////
////    }
    log_debug("Index vysledok %d", myIndex);

    sprintf(gameSocket.buffer, "%d %d %s %d %d",
            IN_GAME,
            gameP.users[myIndex].id,
            gameP.users[myIndex].name,
            gameP.admin, myIndex);
    log_debug("buffer  pre UDP %s", gameSocket.buffer);
    for (int i = 0; i < 10; ++i) {
        if (sendto(gameSocket.sock, &gameSocket.buffer, BUFF_SIZE, 0, (struct sockaddr *) NULL,
                   sizeof(serv_addr)) ==
            -1) {
            log_debug("Error %s %d ", strerror(errno), errno);
        }
    }

//    recvfrom(gameSocket.sock, gameSocket.buffer, sizeof(gameSocket.buffer), 0, (struct sockaddr *) NULL, NULL);
}

enum gameEnum gameCommunication(enum gameEnum commuType, char *data) {
    switch (commuType) {
        case LOGIN:
            log_debug("LOGIN");
//            return loginToServer(data);
            break;
        case SEND:
            if (sendto(gameSocket.sock, &gameSocket.buffer, BUFF_SIZE, 0, (struct sockaddr *) NULL,
                       sizeof(serv_addr)) ==
                -1) {
                log_debug("Error %s %d ", strerror(errno), errno);
            }
            break;
        default:
            log_debug("DEFAULT");
            return ZERO;
    }
}


_Bool socketReadyGame() {
    FD_ZERO(&socketDsGame);
    FD_SET(sdGame, &socketDsGame);
    struct timeval tv;
    tv.tv_usec = 1;

    activityGame = select(sdGame + 1, &socketDsGame, NULL, NULL, &tv);

    if ((activityGame < 0) && (errno != EINTR)) {
        log_error("Select Socket Activity error");
    }
    if (sdGame != 0 && FD_ISSET(sdGame, &socketDsGame)) {
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