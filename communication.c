//
// Created by Jurco on 20. 11. 2018.
//

#include "communication.h"

/**
 * Communication Select
 */
fd_set socketDs;
int sd;
int activity;
//////
struct sockaddr_in address;
struct sockaddr_in serv_addr;

Socket sock;

void initSocket(char *ipAddress, u_int16_t port) {
    sock.sock = 0;

    memset(sock.buffer, '\0', sizeof sock.buffer);
    if ((sock.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr) <= 0) {
        log_error("Invalid address/ Address not supported ");
        printf("Adresa servera nie je dostupna! Adresa servera neexistuje! \n");
        sleep(1);
        exit(EXIT_FAILURE);
    }

    if (connect(sock.sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        log_error("Connection to server Failed  ");
        printf("Nepodarilo sa pripojit na server! Skontrolujte pripojenie. \n");
        sleep(1);
        exit(EXIT_FAILURE);
    }
    sd = sock.sock;

};

_Bool socketReady() {
    FD_ZERO(&socketDs);
    FD_SET(sd, &socketDs);
    struct timeval tv;
    tv.tv_usec = 1;

    activity = select(sd + 1, &socketDs, NULL, NULL, &tv);

    if ((activity < 0) && (errno != EINTR)) {
        log_error("Select Socket Activity error");
    }
    if (sd != 0 && FD_ISSET(sd, &socketDs)) {
        if (recv(sock.sock, sock.buffer, BUFFER_SIZE, 0) == 0) {

            log_fatal("Server disconnected");
            //Close the socket and mark as 0 in list for reuse
            close(sock.sock);
            sock.sock = 0;
            sleep(10);
            exit(EXIT_FAILURE);
        } else {
//            log_debug("data %s", sock.buffer);
            return true;
        }
    }

    return false;
}


enum result_code communication(enum communication_type commuType, char *data) {
    switch (commuType) {
        case LOGIN:
            log_debug("LOGIN");
            return loginToServer(data);
        case CREATE_GAME:
            log_debug("CREATE GAME");
            return createGameToServer(data);
        case FIND_SERVERS:
            findGameFromServer(data);
            return ZERO;
        case JOIN_LOBBY:
            return joinLobbyToServer(data);
        case GET_LOBBY_PLAYER:
            getPlayerInLobby(data);
            return ZERO;
        case LEAVE_LOBBY:
            leaveLobby(data);
            return ZERO;
        case MAP_DOWNLOAD:
            downloadMapFromServer(data);
            return ZERO;
        case START:
            return startGameFromClient(data);
        default:
            log_debug("DEFAULT");
            return ZERO;
    }
}

enum result_code loginToServer(char *data) {
    log_debug("Data: %s", data);
    sprintf(sock.buffer, "%d %d %s", LOGIN, ZERO, data);
    log_debug("Sending to Server for LOGIN: %s", sock.buffer);

    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Sent and Waiting to response for LOGIN");
    recv(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Response %s", sock.buffer);

    int pomT, pomR;
    sscanf(sock.buffer, "%d %d", &pomT, &pomR);
    if ((enum communication_type) pomT == LOGIN) {
        return (enum result_code) pomR;
    }
}

enum result_code createGameToServer(char *data) {
    log_debug("Data: %s", data);
    sprintf(sock.buffer, "%d %d %s", CREATE_GAME, ZERO, data);
    log_debug("Sending to Server for CREATE GAME: %s", sock.buffer);

    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Sent and Waiting to response CREATE GAME");
    recv(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Response %s", sock.buffer);

    int pomT, pomR;
    sscanf(sock.buffer, "%d %d", &pomT, &pomR);
    if ((enum communication_type) pomT == CREATE_GAME) {
        return (enum result_code) pomR;
    }
}


void findGameFromServer(char *data) {
//    log_debug("Data: %s", data);
    sprintf(sock.buffer, "%d %d %s", FIND_SERVERS, ZERO, data);
//    log_debug("Sending to Server for FIND GAMES: %s", sock.buffer);
    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    memset(sock.buffer, '\0', sizeof(sock.buffer));
}

void downloadMapFromServer(char *data) {
    sprintf(sock.buffer, "%d %d %s", MAP_DOWNLOAD, ZERO, data);
    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    int pomT, pomR;
    FILE *fp;
    char fname[20] = "../Mapy/";
    strcat(fname, data);
    strcat(fname, ".txt");
    fp = fopen(fname, "wb+");

    if (NULL == fp) {
        printf("Error opening file");
        sleep(1);
        exit(EXIT_FAILURE);
    }
    do {
        if (socketReady()) {
            int pomT, pomR;
            log_debug("From server Buffer --- %s", sock.buffer);
            sscanf(sock.buffer, "%d %d", &pomT, &pomR);
            if (((enum communication_type) pomT == MAP_DOWNLOAD) && ((enum communication_type) pomR == DONE)) {
                log_debug("Accepting data for map from Server %s", sock.buffer);
                sprintf(sock.buffer, "%d %d", MAP_DOWNLOAD, DONE);
                log_debug("Sending accept finish data for map to Server %s", sock.buffer);
                send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
                break;
            }

            fwrite(sock.buffer, 1, BUFFER_SIZE, fp);
            sprintf(sock.buffer, "%d %d", MAP_DOWNLOAD, OKEJ);
            log_debug("Sending accept data for map to Server %s", sock.buffer);
            send(sock.sock, sock.buffer, BUFFER_SIZE, 0);

        }
    } while (1);
    fclose(fp);
}


void getPlayerInLobby(char *data) {
    sprintf(sock.buffer, "%d %d %s", GET_LOBBY_PLAYER, ZERO, data);
    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    memset(sock.buffer, '\0', sizeof(sock.buffer));

}


enum result_code joinLobbyToServer(char *data) {
    log_debug("Data: %s", data);
    sprintf(sock.buffer, "%d %d %s", JOIN_LOBBY, ZERO, data);
    log_debug("Sending to Server for JOIN LOBBY: %s", sock.buffer);

    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Sent and Waiting to response for JOIN LOBBY");
    recv(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Response %s", sock.buffer);

    int pomT, pomR;
    sscanf(sock.buffer, "%d %d", &pomT, &pomR);
    if ((enum communication_type) pomT == JOIN_LOBBY) {
        return (enum result_code) pomR;
    }

}

void leaveLobby(char *data) {
    sprintf(sock.buffer, "%d %d %s", LEAVE_LOBBY, ZERO, data);
    log_debug("Sending to Server for LEAVE LOBBY: %s", sock.buffer);
    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    memset(sock.buffer, '\0', sizeof(sock.buffer));

}

enum result_code startGameFromClient(char *data) {
    log_debug("Data: %s", data);
    sprintf(sock.buffer, "%d %d %s", START, ZERO, data);
    log_debug("Sending to Server for START GAME: %s", sock.buffer);

    send(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Sent and Waiting to response for START GAME");
    recv(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    log_debug("Response %s", sock.buffer);

    int pomT, pomR;
    sscanf(sock.buffer, "%d %d", &pomT, &pomR);
    if ((enum communication_type) pomT == START) {
        return (enum result_code) pomR;
    }
}


enum result_code resultFromRequest() {
    int pomT, pomR;
    sscanf(sock.buffer, "%d %d", &pomT, &pomR);
    return (enum result_code) pomR;
}

char *dataFromRequest() {
    return sock.buffer;
}

char *readDataFromSocket() {
    recv(sock.sock, sock.buffer, BUFFER_SIZE, 0);
    return sock.buffer;
}

void closeSocket() {
    close(sock.sock);
}
