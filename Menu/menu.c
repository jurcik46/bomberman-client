#include <stdio.h>
#include <curses.h>
#include "../logging/log.h"
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "menu.h"
#include <string.h>

void loginUser(){

}

void menuNewGame(){

}

void menuFindServer(){

}

void menuLeaderBoard(){

}

void mainMenu(WINDOW *my_window){

    const char *choices[4];
    choices[0] = "New Game\n";
    choices[1] = "Find Game\n";
    choices[2] = "LeaderBoard\n";
    choices[3] = "Exit";
    int choice;
    int highlight = 0;

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
        log_info("NewGame");
        menuNewGame();
    } else if(strcmp(choices[highlight], "Find Game") == 0){
        log_info("FindGame");
        menuFindServer();
    } else if(strcmp(choices[highlight], "LeaderBoard") == 0){
        log_info("LeaderBoard");
        menuLeaderBoard();
    } else if(strcmp(choices[highlight], "Exit") == 0){
        log_info("Koniec!");
        exit(0);
    }
    printw("Vybral si moznost: %s", choices[highlight]);
}