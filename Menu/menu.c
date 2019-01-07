#include "menu.h"

/**
 * Funkcia nainicializuje kniznicu ncurses t.j. nastaví obrazovku, pociatocne X a Y hodnoty (rozmery okna) a
 * povolí pouzivanie klaves
 */
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
 * Funkcia sluzi na prihlasenie uzivatela do hry
 * Ak nema vytvoreny ucet tak ho registruje
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
    //Osetrenie prazdneho vstupu mena
    while (strlen(user.name) == 0){
        mvwprintw(my_window, 6, 1, "Zadaj meno(nick): ");
        wgetstr(my_window, user.name);
    }
    mvwprintw(my_window, 8, 1, "Zadaj heslo: ");
    wrefresh(my_window);
    noecho();
    wgetstr(my_window, user.password);
    //Osetrenie prazdneho vstupu hesla
    while (strlen(user.password) == 0){
        mvwprintw(my_window, 8, 1, "Zadaj heslo: ");
        wrefresh(my_window);
        noecho();
        wgetstr(my_window, user.password);
    }

    char data[BUFFER_SIZE];
    sprintf(data, "%s %s", user.name, user.password);

    enum result_code result = communication(LOGIN, data);
    switch (result) {
        case OKEJ:
            mvwprintw(my_window, 10, 1, "Prihlasenie prebehlo USPESNE!\n");
            break;
        case CREATED:
            log_debug("Acc was created");
            mvwprintw(my_window, 10, 1, "Registracia prebehla USPESNE!\n");
            break;
        case UNAUTHORIZED:
            log_debug("Login failed");
            mvwprintw(my_window, 10, 1, "Prihlasenie bolo NEUSPESNE!\n");
            break;
        case INTERNAL_SERVER_ERROR:
            log_debug("Server Error");
            mvwprintw(my_window, 10, 1, "Problem pri komunikacii so serverom.\n");
            break;
        default:;
    }
    sleep(1);
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
    char data[BUFFER_SIZE];
    sprintf(data, "%s %d %d", game.nazovHry, game.cisloMapy, game.pocetHracov);

    enum result_code result = communication(CREATE_GAME, data);
    switch (result) {
        case CREATED:
            game.users[0] = user;
            game.users[0].admin = true;
            log_debug("Game was created");
            return true;
        case UNAUTHORIZED:
            log_debug("Create game failed");
            return false;
        case INTERNAL_SERVER_ERROR:
            log_debug("Server Error");
            return false;
        default:;
            return false;

    }
    //TODO treba tu doplnit funkciu co posle info o hre na server a ak server odpovie OKEJ tak funkcia vrati hodnotu (true) a v maine
    //TODO sa zavola funkcia menuLobby
    //TODO treba zmenit aj navratovu hodnotu funkcie
}

void *handleUserInput(void* param) {
    CHOICE *choice = (CHOICE*)param;
    int moznost;

    pthread_mutex_lock(&choice->mutex);
    _Bool result = choice->result;
    WINDOW *window = choice->lobby_Win;
    pthread_mutex_unlock(&choice->mutex);

    while(!result){
        moznost = wgetch(window);

        pthread_mutex_lock(&choice->mutex);
        result = choice->result;
        choice->choice = moznost;
        pthread_mutex_unlock(&choice->mutex);
    }
    pthread_exit(0);
}

int menuLobby(WINDOW *my_window, int startY, int startX) {
    wclear(my_window);

    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LOBBY\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);

    const char *choices[2];
    choices[0] = "Start Game";
    choices[1] = "Leave Game";

    int highlight = 0;

    CHOICE param;
    param.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&param.mutex);
    param.lobby_Win = newwin(LOBBY_WIN_SIZE, WIN_WIDTH, startY + WIN_HEIGHT, startX);
    keypad(param.lobby_Win, true);
    wclear(param.lobby_Win);
    param.result = false;
    pthread_mutex_unlock(&param.mutex);

    pthread_t userInputThread;
    pthread_create(&userInputThread, NULL, handleUserInput, (void *)&param);

    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight)
                wattron(param.lobby_Win, A_REVERSE);
            mvwprintw(param.lobby_Win, i + 1, 1, choices[i]);
            wattroff(param.lobby_Win, A_REVERSE);
        }

    pthread_mutex_lock(&param.mutex);
    int choice = param.choice;
    pthread_mutex_unlock(&param.mutex);

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
            case ENTER:
                pthread_mutex_lock(&param.mutex);
                mvwprintw(param.lobby_Win, 1, 1, "             ");
                mvwprintw(param.lobby_Win, 2, 1, "             ");
                wrefresh(param.lobby_Win);
                delwin(param.lobby_Win);
                param.result = true;
                pthread_mutex_unlock(&param.mutex);
                pthread_join(userInputThread, NULL);
                pthread_mutex_destroy(&param.mutex);
                return highlight;
            default:
                break;
        }
    }
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
        if (choice == ENTER)
            break;
    }
    return highlight;
}