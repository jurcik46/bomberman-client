//
// Created by Jurco on 20. 11. 2018.
//

#include <arpa/inet.h>
#include "communication.h"


void initSocket(char *ipAddress, u_int16_t port) {
    sock = 0;
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

void closeSocket() {
    close(sock);
}
