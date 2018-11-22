//    log_trace(const char *fmt, ...);
//    log_debug(const char *fmt, ...);
//    log_info(const char *fmt, ...);
//    log_warn(const char *fmt, ...);
//    log_error(const char *fmt, ...);
//    log_fatal(const char *fmt, ...);

//    log_debug("Hello %s", "world");
//    log_info("Hello %s", "world");
//    log_warn("Hello %s", "world");
//    log_error("Hello %s", "world");

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>
#include "logging/log.h"
#include "Menu/menu.h"


int main() {


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

