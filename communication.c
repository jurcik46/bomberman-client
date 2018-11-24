//
// Created by Jurco on 20. 11. 2018.
//

#include "communication.h"


void initSocket(char *ipAddress, u_int16_t port) {
    sock = 0;
    memset(buffer, '\0', sizeof buffer);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr) <= 0) {
        log_error("Invalid address/ Address not supported ");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        log_error("Connection Failed ");
        exit(EXIT_FAILURE);
    }


};


enum result_code communication(enum communication_type commuType, char *data) {

    switch (commuType) {
        case LOGIN:
            log_debug("LOGIN");
            return loginToServer(data);
        default:
            log_debug("DEFAULT");
            return ZERO;
    }
}

enum result_code loginToServer(char *data) {
    log_debug("Data: %s", data);
    sprintf(buffer, "%d %d %s", LOGIN, ZERO, data);
    log_debug("Sending to Server: %s", buffer);

    send(sock, buffer, BUFFER_SIZE, 0);
    log_debug("Sent and Waiting to response");
    recv(sock, buffer, BUFFER_SIZE, 0);
    log_debug("Response %s", buffer);

    int pomT, pomR;
//    char serverData[BUFFER_SIZE];
    sscanf(buffer, "%d %d", &pomT, &pomR);
    if ((enum communication_type) pomT == LOGIN) {
        return (enum result_code) pomR;
    }
}

void closeSocket() {
    close(sock);
}
