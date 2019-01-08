#include <stdio.h>
#include <curses.h>
#include "logging/log.h"
#include <unistd.h>
#include <stdlib.h>

#include "logging/log.h"
#include "communication.h"
#include "Menu/menu.h"

#define LOG_FILE_PATH "logs.log"
#define ADDRESS "127.0.0.1"
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
    delwin(my_window);
    endwin();
    fclose(logFile);
};

//

int main(int argc, char *argv[]) {
    FILE *logFile = fopen(LOG_FILE_PATH, "w+");

    loggerInit(logFile);

    initNcurses();

    initSocket(ADDRESS, PORT);

    loginUser(my_window);
////Funkcia zisťuje či hrač v lobby spustil hru alebo ju oputil
////Ak opustil lobby vrati ho do mainMenu inak spusti hru
    menu();
    closingApp(logFile);
}
