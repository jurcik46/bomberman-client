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

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
    wrefresh(local_win);		/* Show that box 		*/

    return local_win;
}

int main() {

//    log_set_quiet(0);
//    log_set_level(LOG_DEBUG);
//    FILE *logFile = fopen("logs.log", "w+");
//    log_set_fp(logFile);
//
//    if (logFile == NULL) {
//        printf("Error! opening file");
//        // Program exits if the file pointer returns NULL.
//        return 1;
//    }

    WINDOW *my_window;
//    WINDOW *menuLobbyWin;
    int startX, startY;
    //int LobbyWinSize = 3;
    int choice = 0;
    bool success;

    initscr();
    cbreak();

//    heigh = 20;
//    width = 90;
    startX = (COLS - WIN_WIDTH ) / 2;
    startY = (LINES - WIN_HEIGHT ) / 2;

    my_window = newwin(WIN_HEIGHT, WIN_WIDTH, startY, startX);
//    menuLobbyWin = newwin(LobbyWinSize, width, startY + heigh, startX);
    keypad(my_window, true);
//    keypad(menuLobbyWin, true);

////Funkcia sluzi na prihlasenie uzivatela do hry
////Ak nema vytvoreny ucet tak ho registruje
//    loginUser(my_window);

////Funkcia zisťuje či hrač v lobby spustil hru alebo ju oputil
////Ak opustil lobby vrati ho do mainMenu inak spusti hru
//    choice = menuLobby(my_window, startY, startX);
//    if(choice == 0){
//        printw("Start Game");
//        //TODO treba dorobit spustenie hry
//    }else if(choice == 1){
//        mainMenu(my_window);
//    }

    choice = mainMenu(my_window);
while(choice != 3){
    if(choice == 0){
        success = menuNewGame(my_window);
        if(success){
            choice = menuLobby(my_window, startY, startX);
            if(choice == 0){
                //START GAME
            }else if(choice == 1){
                choice = mainMenu(my_window);
            }
        } else{
            wprintw(my_window, "Nepodarilo sa vytvoriť hru!");
            wrefresh(my_window);
            choice = menuNewGame(my_window);
        }
    } else if(choice == 1){
        menuFindServer(my_window);
    } else if(choice == 2){
        menuLeaderBoard(my_window);
    }
}

printw("END GAME!");


////Funkcia spusti uvodne menu kde si hrac vyberie z moznosti
//    choice = mainMenu(my_window);
//    if(choice == 0){
//       success = menuNewGame(my_window);
//       if(success){
//           choice = menuLobby(my_window, startY, startX);
//           if(choice == 0){
//               //START GAME
//           }else if(choice == 1){
//               mainMenu(my_window);
//           }
//       } else{
//           wprintw(my_window, "Nepodarilo sa vytvoriť hru!");
//           wrefresh(my_window);
//           menuNewGame(my_window);
//       }
//    } else if(choice == 1){
//        menuFindServer(my_window);
//    } else if(choice == 2){
//        menuLeaderBoard(my_window);
//    } else if(choice == 3){
//        return 1;
//    }
    wrefresh(my_window);

    refresh();
    getch();
    delwin(my_window);
    endwin();


//        box(stdscr,0,0);
//        wborder(stdscr,'|','|','-','-','+','+','+','+');
//        refresh();
//        getch();
//        endwin();

    //fclose(logFile);
    return 0;
}

