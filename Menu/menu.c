#include <stdio.h>
#include <curses.h>
#include "../logging/log.h"
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "menu.h"
#include <string.h>

void loginUser(WINDOW *my_window){
    wclear(my_window);
    mvwprintw(my_window, 1, 20, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LOGIN\n");
    mvwprintw(my_window, 4, 1, "_________________________________________________\n");
    mvwprintw(my_window, 6, 1, "Zadaj meno(nick): ");
    wrefresh(my_window);
    wgetstr(my_window, user.name);
    mvwprintw(my_window, 8, 1, "Zadaj heslo: ");
    wrefresh(my_window);
    noecho();
    wgetstr(my_window, user.password);
}

void menuNewGame(WINDOW *my_window){
    wclear(my_window);
    echo();
    mvwprintw(my_window, 1, 20, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "CREATING NEW GAME\n");
    mvwprintw(my_window, 4, 1, "_________________________________________________\n");
    wrefresh(my_window);
    mvwprintw(my_window, 6, 1, "Zadaj nazov hry: ");
    wrefresh(my_window);
    wgetstr(my_window, game.nazovHry);
    mvwprintw(my_window, 8, 1, "Zadaj cislo mapy: ");
    wrefresh(my_window);
    //scanw("%d", &game.cisloMapy);
    wscanw(my_window, "%d", &game.cisloMapy);
    mvwprintw(my_window, 10, 1, "Zadaj pocet hracov: ");
    wrefresh(my_window);
    scanw("%d", &game.pocetHracov);
    //wscanw(my_window, "%d", &game.pocetHracov);

    printw("nazov: %s mapa: %d hraci: %d", game.nazovHry, game.cisloMapy, game.pocetHracov);
}

void menuFindServer(WINDOW *my_window){
    wclear(my_window);

}

void menuLeaderBoard(WINDOW *my_window){
    wclear(my_window);

}

void mainMenu(WINDOW *my_window){

    const char *choices[4];
    choices[0] = "New Game";
    choices[1] = "Find Game";
    choices[2] = "LeaderBoard";
    choices[3] = "Exit";
    int choice;
    int highlight = 0;
    wclear(my_window);
    mvwprintw(my_window, 1, 20, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "MENU\n");
    mvwprintw(my_window, 4, 1, "_________________________________________________\n");
    wrefresh(my_window);

    while(1){
        for (int i = 0; i < 4; i++) {
            if(i == highlight)
                wattron(my_window, A_REVERSE);
            mvwprintw(my_window, i+6, 1, choices[i]);
            wattroff(my_window, A_REVERSE);
        }
        choice = wgetch(my_window);

        switch(choice){
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 4)
                    highlight = 3;
                break;
            default:
                break;
        }
        if(choice == 10)
            break;
    }

    if(strcmp(choices[highlight], "New Game") == 0){
        menuNewGame(my_window);
    } else if(strcmp(choices[highlight], "Find Game") == 0){
        menuFindServer(my_window);
    } else if(strcmp(choices[highlight], "LeaderBoard") == 0){
        menuLeaderBoard(my_window);
    } else if(strcmp(choices[highlight], "Exit") == 0){
        exit(0);
    }
}