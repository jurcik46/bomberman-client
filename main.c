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

void menu(){
    choice = mainMenu(my_window);
    while (choice != EXIT){
        switch (choice){
            case MENU_NEW_GAME:
                success = menuNewGame(my_window);
                if (success) {
                    choice = menuLobby(my_window, startY, startX);
                    if (choice == START_GAME) {
                        //START GAME
                        printf("START GAME");
                    } else if (choice == MAIN_MENU) {
                        choice = mainMenu(my_window);
                    }
                } else {
                    wprintw(my_window, "Nepodarilo sa vytvoriť hru!");
                    wrefresh(my_window);
                    choice = menuNewGame(my_window);
                }
                break;
            case MENU_FIND_SERVER:
                menuFindServer(my_window);
                break;
            case MENU_LEADER_BOARD:
                menuLeaderBoard(my_window);
                break;
            case MENU_EXIT:
                choice = EXIT;
                break;
            default :
                printf("Invalid choice!");
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *logFile = fopen(LOG_FILE_PATH, "w+");

    loggerInit(logFile);

    initNcurses();

    //initSocket("127.0.0.1", PORT);

//    char *hello = "Hello from client";
//    send(sock, hello, strlen(hello), 0);
//    printf("Hello message sent\n");
//    read(sock, buffer, BUFFER_SIZE);
//    printf("%s\n", buffer);
//    sleep(10);

    //loginUser(my_window);

    menu();

    closingApp(logFile);
    return 0;


}