#include <stdio.h>
#include <curses.h>
#include "logging/log.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "logging/log.h"
//#include "communication.h"
#include "Menu/menu.h"
#include "Hra/mapa.h"
#include "Hra/hra.h"
#include "logging/log.h"
#include "communication.h"
#include "constants.h"
#include "Hra/gameCommunication.h"

#define LOG_FILE_PATH "logs.log"
#define ADDRESS "127.0.0.1"
#define ADDRESS_JANO "158.193.102.40"
#define PORT 8080

#define FINDING_DIR "../Mapy"
#define CREATE_Mapy_dir "../Mapy"

/**
 * Funkcia pomocou ktorej sa inicializuju logy (debug)
 * @param logFile - subor ktory sluzi na logy (debug)
 */
void loggerInit(FILE *logFile) {

    if (logFile == NULL) {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(EXIT_FAILURE);
    }
    log_set_quiet(5);
    log_set_level(LOG_DEBUG);
    log_set_fp(logFile);
}

/**
 * Funkcia ukoncuje aplikaciu.
 * Zatvara vytvoreny socket, maže vytvorene okna a ukoncuje ich.
 * @param logFile - subor ktory sluzi na logy (debug)
 */
void closingApp(FILE *logFile) {
    closeSocket();
    closeMenu();
    endwin();
    fclose(logFile);
};

void createDirectory() {
    struct stat st = {0};
    int resultStatus = stat(FINDING_DIR, &st);
    printf("Result %d\n", resultStatus);

    if (resultStatus == -1) {
        if (mkdir(CREATE_Mapy_dir, 0644) == 0) {
            printf("Vytvoril sa subor.\n");
        }
    } else {
        printf("Subor uz existuje.\n");
    }
}


int main(int argc, char *argv[]) {
    createDirectory();
    FILE *logFile = fopen(LOG_FILE_PATH, "w+");
    loggerInit(logFile);
    initSocket(ADDRESS_JANO, PORT);

    initNcurses();

    loginUser();

    menu();
    closingApp(logFile);
}
