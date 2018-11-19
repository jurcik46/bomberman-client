#include <stdio.h>
#include <curses.h>
#include "logging/log.h"
#include <unistd.h>
#include <stdlib.h>
#define DELAY 30000

void nacitajMapu(){
    FILE * vstup;
    if ((vstup = fopen("mapa.txt", "r")) == NULL)
    {
    int riadok,stlpec;
//    while(){};

}

}

/**
 * alokovanie pamete pre mapu
 * @param m riadok
 * @param n stlpec
 * @return smernik dvojrozmerne pole
 */
char** createM(int m, int n) {
    char **mat;
    mat = malloc(m * sizeof (*mat));
    for (int i = 0; i < m; i++) {
        mat[i] = calloc(n, sizeof (char));
    }
    return mat;
}

/**
 * Uvolnenie pamete pre mapu
 * @param m
 * @param mat
 */

    void deletM(int m, char ***mat) {
        for (int i = 0; i < m; i++) {
            free((*mat)[i]);
        }
        free((*mat));
        *mat = NULL;

    }

/**
* Inicializovane ncurse kniznic
*/

void initCurses() {

    initscr(); //pre vytvorenie ncurse win
    start_color(); //aktivacia farieb
    curs_set(0);
//    nodelay(stdscr, TRUE); //getch bez pauzy
    nonl();
    cbreak();
    noecho(); //nezobrazovat vstupne tlacitka
    init_color(COLOR_WHITE, 0, 255, 0);

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);

}

/*
 * Vytvorenie okna pre ncurse na knzolu
 * Parametre velkost okna
 */
WINDOW * win;

WINDOW * status;

void createWindows(int y, int x, int y0, int x0) {
    //vytvorenie okien na hru a na konzolu
//    status = newwin(3, 50, y, 1);
    win = newwin(y, x, y0, x0);
    wrefresh(win);
}



/**
 * Funckia na vypis moznosti urovne
 */



void setUroven() {

//    wattron(win, COLOR_PAIR(PACMAN));
    attron(COLOR_PAIR(1));
    mvwprintw(win, 1, 15, "Vytajte v hre Pacman ");
    mvwprintw(win, 3, 1, "Vyberte si uroven hry");
    mvwprintw(win, 5, 5, "Easy [0]");
    mvwprintw(win, 6, 5, "Medium [1]");
    mvwprintw(win, 7, 5, "Hard [2]");
    mvwprintw(win, 8, 5, "Ukoncit aplikaciu [3]");
    wrefresh(win);



}

int main() {
    initCurses(); //Pre zapnutie ncurse
    WINDOW * win;
    win = newwin(50, 50, 1, 1);
    wrefresh(win);
//    createWindows(40, 40, 1, 1); // vytvorenie okna
//    initscr(); //pre vytvorenie ncurse win
//    createWindows(40, 40, 1, 1); // vytvorenie okna

    log_set_quiet(0);
    log_set_level(LOG_DEBUG);
    FILE *logFile = fopen("logs.log", "w+");
    log_set_fp(logFile);

    if (logFile == NULL) {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        return 1;
    }
    refresh();

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
//    mvprintw(1, 15, "Vytajte v hre Pacman ");
//    setUroven();
    attron(COLOR_PAIR(1));
    mvwprintw(win, 1, 15, "Vytajte v hre Pacman ");
    wrefresh(win);
    getch();            /* Wait for user input */

    delwin(win);
    endwin();
    fclose(logFile);
    return 0;


}