#include <stdio.h>
#include <curses.h>
#include "logging/log.h"
#include <unistd.h>
#include <stdlib.h>

#include "logging/log.h"
#include "communication.h"
#include "Menu/menu.h"

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
    delwin(my_window);
    endwin();
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
    initNcurses();
    loginUser(my_window);

////Funkcia zisťuje či hrač v lobby spustil hru alebo ju oputil
////Ak opustil lobby vrati ho do mainMenu inak spusti hru

    choice = mainMenu(my_window);
    while (choice != 15) {
        if (choice == 0) {
            success = menuNewGame(my_window);
            if (success) {
                choice = menuLobby(my_window, startY, startX);
                if (choice == 0) {
                    //START GAME
                } else if (choice == 1) {
                    choice = mainMenu(my_window);
                }
            } else {
                wprintw(my_window, "Nepodarilo sa vytvoriť hru!");
                wrefresh(my_window);
                choice = menuNewGame(my_window);
            }
        } else if (choice == 1) {
            menuFindServer(my_window);
        } else if (choice == 2) {
            menuLeaderBoard(my_window);
        } else if (choice == 3) {
            choice = 15;//preto 15 lebo taka moznost sa nepouziva nikde
        }
    }


    delwin(my_window);
    endwin();

    return 0;


}