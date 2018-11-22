#include "menu.h"

void initNcurses() {
    initscr();
    cbreak();
    choice = 0;
    startX = (COLS - WIN_WIDTH) / 2;
    startY = (LINES - WIN_HEIGHT) / 2;
    my_window = newwin(WIN_HEIGHT, WIN_WIDTH, startY, startX);
    keypad(my_window, true);
}

/**
 * ////Funkcia sluzi na prihlasenie uzivatela do hry
////Ak nema vytvoreny ucet tak ho registruje
 * @param my_window
 */
void loginUser(WINDOW *my_window) {
    wclear(my_window);
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LOGIN\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    mvwprintw(my_window, 6, 1, "Zadaj meno(nick): ");
    wrefresh(my_window);
    wgetstr(my_window, user.name);
    mvwprintw(my_window, 8, 1, "Zadaj heslo: ");
    wrefresh(my_window);
    noecho();
    wgetstr(my_window, user.password);
    //TODO treba doplniť aby user odoslal meno a heslo na server
    //TODO ten mu odpovie ci sa prihlasil alebo nie a nasledne bud spusti mainMenu alebo ho presmeruje znova na login
}

bool menuNewGame(WINDOW *my_window) {
    wclear(my_window);
    echo();
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "CREATING NEW GAME\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);
    mvwprintw(my_window, 6, 1, "Zadaj nazov hry: ");
    wrefresh(my_window);
    wgetstr(my_window, game.nazovHry);
    mvwprintw(my_window, 8, 1, "Zadaj cislo mapy: ");
    wrefresh(my_window);
    wscanw(my_window, "%d", &game.cisloMapy);
    mvwprintw(my_window, 10, 1, "Zadaj pocet hracov(max 4): ");
    wrefresh(my_window);
    wscanw(my_window, "%d", &game.pocetHracov);

    //printw("nazov: %s mapa: %d hraci: %d\n", game.nazovHry, game.cisloMapy, game.pocetHracov);

    //TODO treba tu doplnit funkciu co posle info o hre na server a ak server odpovie OK tak funkcia vrati hodnotu (true) a v maine
    //TODO sa zavola funkcia menuLobby
    //TODO treba zmenit aj navratovu hodnotu funkcie
    return true;
}

int menuLobby(WINDOW *my_window, int startY, int startX) {
    WINDOW *lobby_Win;
    lobby_Win = newwin(LOBBY_WIN_SIZE, WIN_WIDTH, startY + WIN_HEIGHT, startX);
    keypad(lobby_Win, true);
    wclear(my_window);
    wclear(lobby_Win);

    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LOBBY\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);

    const char *choices[2];
    choices[0] = "Start Game";
    choices[1] = "Leave Game";
    int choice;
    int highlight = 0;

    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight)
                wattron(lobby_Win, A_REVERSE);
            mvwprintw(lobby_Win, i + 1, 1, choices[i]);
            wattroff(lobby_Win, A_REVERSE);
        }
        choice = wgetch(lobby_Win);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 2)
                    highlight = 1;
                break;
            default:
                break;
        }
        if (choice == 10) {
            mvwprintw(lobby_Win, 1, 1, "             ");
            mvwprintw(lobby_Win, 2, 1, "             ");
            wrefresh(lobby_Win);
            delwin(lobby_Win);
            break;
        }
    }
    return highlight;
    //printw("Vybral si moznost: %d -> %s\n", highlight, choices[highlight]);
}

void menuFindServer(WINDOW *my_window) {
    wclear(my_window);
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "FINDING GAME\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);
    //TODO Dorobit funkciu na prijmanie sprav od servera o vytvorenych hrach
    //TODO a nasledne ich vypisat
    //TODO doplnit ze ked stlaci ESC tak ho da Back To MainMenu

}

void menuLeaderBoard(WINDOW *my_window) {
    wclear(my_window);
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LEADER BOARD\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    mvwprintw(my_window, 6, 1, "Name\t| Wins\t| Loses\t| Kills\t| Deaths | Played Games");
    //TODO Treba vytvoriť funkciu pre vypis statistiky z databazy
    //TODO dorobiť nove okno s moznostami vyberu zoradenia statistiky
    wrefresh(my_window);

}

int mainMenu(WINDOW *my_window) {

    const char *choices[4];
    choices[0] = "New Game";
    choices[1] = "Find Game";
    choices[2] = "LeaderBoard";
    choices[3] = "Exit";
    int choice;
    int highlight = 0;
    wclear(my_window);
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "MENU\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);

    while (1) {
        for (int i = 0; i < 4; i++) {
            if (i == highlight)
                wattron(my_window, A_REVERSE);
            mvwprintw(my_window, i + 6, 1, choices[i]);
            wattroff(my_window, A_REVERSE);
        }
        choice = wgetch(my_window);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 4)
                    highlight = 3;
                break;
            default:
                break;
        }
        if (choice == 10)
            break;
    }
    return highlight;
}