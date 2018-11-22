#include <stdio.h>
#include <curses.h>
#include "logging/log.h"
#include <unistd.h>
#include <stdlib.h>

#include "logging/log.h"
#include "communication.h"

#define LOG_FILE_PATH "logs.log"
#define PORT 8080

void loggerInit(FILE *logFile) {

    if (logFile == NULL) {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(EXIT_FAILURE);
    }
    log_set_quiet(0);
    log_set_level(LOG_DEBUG);
    log_set_fp(logFile);
}

void closingApp(FILE *logFile) {
    closeSocket();
    fclose(logFile);
};

int main(int argc, char *argv[]) {

    FILE *logFile = fopen(LOG_FILE_PATH, "w+");
    loggerInit(logFile);

    initSocket("127.0.0.1", PORT);
    char *hello = "Hello from client";
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    read(sock, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);
    sleep(10);

    closingApp(logFile);
    return 0;


}