#include "menu.h"

WINDOW *my_window;
int startX, startY;
int choice;
bool success;
struct game game;
struct game emptyGame;
CHOICE param;
CHOICE paramEmpty;
User user;


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
    refresh();
    my_window = newwin(WIN_HEIGHT, WIN_WIDTH, startY, startX);
    keypad(my_window, true);
}

static _Bool startGame() {
    wclear(my_window);
    mvwprintw(my_window, 8, 10, "Downloading map...");
    wrefresh(my_window);
    sleep(1);
    wclear(my_window);
//    raise(SIGINT);
    char data[BUFFER_SIZE];
    int pom;
    char ipAddress[INET_ADDRSTRLEN];
    int port;

//    if (game.admin)
    sscanf(dataFromRequest(), "%d %d %s %d", &pom, &pom, ipAddress, &port);
    log_debug("dataFromRequest    %s", dataFromRequest);
//    if (!game.admin)
//        sscanf(readDataFromSocket(), "%d %d %s %d", &pom, &pom, ipAddress, &port);

    sprintf(data, "%d", game.cisloMapy);
//    communication(MAP_DOWNLOAD, data);
//    initGameSocket(ipAddress, (u_int16_t) port, game);
    initMap(game.cisloMapy, game.pocetHracov);
}


void menu() {
    choice = mainMenu(my_window);
    while (choice != EXIT) {
        switch (choice) {
            case MENU_NEW_GAME:
                if (!success) {
                    success = menuNewGame(my_window);
                }
                if (success) {
                    choice = menuLobby(my_window, startY, startX);
                    if (choice == START_GAME) {
                        char data[BUFFER_SIZE];
                        sprintf(data, "%d", game.gameId);


                        switch (communication(START, data)) {
                            case OKEJ:
                                startGame();
                                break;
                            case NOT_FOUND:
                                //TODO hra sa nenasla  na servery a neda sa spustit INFO PRE hraca
                                break;
                            default :
                                break;
                        }
                    } else if (choice == MAIN_MENU) {
                        char data[BUFFER_SIZE];
                        sprintf(data, "%d %d %d", game.gameId, user.id, game.admin);
                        communication(LEAVE_LOBBY, data);
                        game = emptyGame;
                        choice = mainMenu(my_window);
                    }
                    success = false;
                } else {
                    wprintw(my_window, "Nepodarilo sa vytvoriť hru!");
                    wrefresh(my_window);
                    choice = MENU_NEW_GAME;
                }
                break;
            case MENU_FIND_SERVER:
                choice = menuFindServer(my_window);
                if (choice == JOIN) {
                    success = true;
                    choice = MENU_NEW_GAME;
                    break;
                }
                if (choice == ESC)
                    choice = mainMenu(my_window);
                break;
            case MENU_LEADER_BOARD:
                menuLeaderBoard(my_window);
                break;
            case MENU_EXIT:
                choice = EXIT;
                break;
            default :
                break;
        }
    }
}

/**
 * Funkcia sluzi na prihlasenie uzivatela do hry
 * Ak nema vytvoreny ucet tak ho registruje
 * @param my_window
 */
void loginUser() {
    wclear(my_window);
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LOGIN\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    mvwprintw(my_window, 6, 1, "Zadaj meno(nick): ");
    wrefresh(my_window);
    echo();
    wgetstr(my_window, user.name);
    //Osetrenie prazdneho vstupu mena
    while (strlen(user.name) == 0) {
        mvwprintw(my_window, 6, 1, "Zadaj meno(nick): ");
        wgetstr(my_window, user.name);
    }
    mvwprintw(my_window, 8, 1, "Zadaj heslo: ");
    wrefresh(my_window);
    noecho();
    wgetstr(my_window, user.password);
    //Osetrenie prazdneho vstupu hesla
    while (strlen(user.password) == 0) {
        mvwprintw(my_window, 8, 1, "Zadaj heslo: ");
        wrefresh(my_window);
        noecho();
        wgetstr(my_window, user.password);
    }

    char data[BUFFER_SIZE];
    sprintf(data, "%s %s", user.name, user.password);
    int pom = 0;
    enum result_code result = communication(LOGIN, data);
    switch (result) {
        case OKEJ:
            sscanf(dataFromRequest(), "%d %d %d", &pom, &pom, &user.id);
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "LOGIN\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "Prihlasenie prebehlo USPESNE!\n");
            wrefresh(my_window);
            user.amI = true;
            sleep(1);
            break;
        case CREATED:
            sscanf(dataFromRequest(), "%d %d %d", &pom, &pom, &user.id);
//            mvwprintw(my_window, 10, 1, "Registracia prebehla USPESNE!\n");
//            sleep(1);
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "LOGIN\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "Registracia prebehla USPESNE!\n");
            wrefresh(my_window);
            user.amI = true;
            sleep(1);
//            log_debug("Acc was created");
            break;
        case UNAUTHORIZED:
//            log_debug("Login failed");
//            mvwprintw(my_window, 10, 1, "Prihlasenie bolo NEUSPESNE!\n");
//            sleep(1);
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "LOGIN\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "Prihlasenie bolo NEUSPESNE!\n");
            wrefresh(my_window);
            sleep(1);
            loginUser();
            break;
        case INTERNAL_SERVER_ERROR:
//            log_debug("Server Error");
//            mvwprintw(my_window, 10, 1, "Problem pri komunikacii so serverom.\n");
//            sleep(1);
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "LOGIN\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "Problem pri komunikacii so serverom.\n");
            wrefresh(my_window);
            sleep(1);
            loginUser();
            break;
        case SERVICE_UNAVAILABLE:
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "LOGIN\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "Hrac uz je prihlaseny.\n");
            wrefresh(my_window);
            sleep(1);
            loginUser();
            break;
        default:;
    }
}

/**
 * Funkcia sluzi na vytvorenie novej hry
 * @param my_window - okno v ktorom sa ma vykreslit GUI pre uzivatela
 * @return - navratova hodnota je true ak sa hru podarilo vytvorit a false ak nie
 */
bool menuNewGame(WINDOW *my_window) {
    wclear(my_window);
    echo();
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "CREATING NEW GAME\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);

    //Osetrenie prazdneho vstupu nazvu hry
    while (strlen(game.nazovHry) == 0) {
        mvwprintw(my_window, 6, 1, "Zadaj nazov hry:                     ");
        wrefresh(my_window);
        wgetstr(my_window, game.nazovHry);
    }

    _Bool isSaved = false;
    int value = -1;
    int input;

//Osetrenie vstupu pre zadavanie cisla mapy (len INT-y)
    while (!isSaved) {

        //Osetrenie prazdneho vstupu pri cisle mapy
        while (value < 0) {
            mvwprintw(my_window, 8, 1, "Zadaj cislo mapy:                    ");
            wrefresh(my_window);
            input = wscanw(my_window, "%d", &value);

            if (input == EOF) {
//            log_debug("Uzivatel ukoncil zadavanie z klavesnice. ");
                isSaved = false;
                break;
            } else if (input == 0) {
                mvwprintw(my_window, 9, 1, "Zadat mozes iba CISLA! ");
                mvwprintw(my_window, 8, 1, "Zadaj cislo mapy:                    ");
                wrefresh(my_window);
                isSaved = false;
            } else {
                game.cisloMapy = value;
                isSaved = true;
            }
        }
    }

    isSaved = false;
    value = -1;

//Osetrenie vstupu pre zadavanie poctu hracov (len INT-y)
    while (!isSaved) {

        //Osetrenie prazdneho vstupu pri pocte hracov
        while (value < 0) {
            mvwprintw(my_window, 10, 1, "Zadaj pocet hracov(max 4):           ");
            wrefresh(my_window);
            input = wscanw(my_window, "%d", &value);

            if (input == EOF) {
//            log_debug("Uzivatel ukoncil zadavanie z klavesnice. ");
                isSaved = false;
                break;
            } else if (input == 0) {
                mvwprintw(my_window, 11, 1, "Zadat mozes iba CISLA! ");

                wrefresh(my_window);
                isSaved = false;
            } else if (value > 4) {
                mvwprintw(my_window, 11, 1, "MAXIMALNY pocet hracov je 4! ");
                wrefresh(my_window);
                isSaved = false;
            } else if (value < 1) {
                mvwprintw(my_window, 11, 1, "MINIMALNY pocet hracov je 1! ");
                wrefresh(my_window);
                isSaved = false;
            } else {
                game.maxPocetHracov = value;
                isSaved = true;
            }
        }
    }

    char data[BUFFER_SIZE];
    sprintf(data, "%s %d %d", game.nazovHry, game.cisloMapy, game.maxPocetHracov);
    enum result_code result = communication(CREATE_GAME, data);
    log_debug("result %d", result);
    switch (result) {
        case CREATED:
            game.users[0] = user;
            game.pocetHracov++;
            game.admin = true;
            game.users[0].amI = true;
            log_debug("%s", dataFromRequest());
            sscanf(dataFromRequest(), "%d %d %d", &game.gameId, &game.gameId, &game.gameId);
//            game.users[game.pocetHracov] = user;
            log_debug("Game was created");
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "CREATING NEW GAME\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "PODARILO sa uspesne vytvorit hru!\n");
            wrefresh(my_window);
            sleep(1);
            return true;
        case SERVICE_UNAVAILABLE:
            log_debug("Server Full");
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "CREATING NEW GAME\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "NEPODARILO sa vytvorit hru! Server je plny.\n");
            wrefresh(my_window);
            sleep(1);
            return false;
        case NOT_FOUND:
            log_debug("MAP NOT FOUND");
            wclear(my_window);
            mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
            mvwprintw(my_window, 3, 10, "CREATING NEW GAME\n");
            mvwprintw(my_window, 4, 1,
                      "_________________________________________________________________________________________\n");
            mvwprintw(my_window, 7, 5, "NEPODARILO sa vytvorit hru! Mapa sa nenasla\n");
            wrefresh(my_window);
            sleep(1);
            return false;
        default:;
            log_debug("DEFAULT  ");
            return false;
    }
}

/**
 * Funkcia ktoru pouziva vedlajsie vlakno na obsluzenie vstupu od uzivatela
 * ktory si môže vybrat si hru spusti alebo z hry odide.
 * @param param
 * @return
 */
void *handleUserInput() {
    int moznost;
    pthread_mutex_lock(&param.mutex);
    _Bool result = param.resultLobby;
    WINDOW *window = param.lobby_Win;
    pthread_mutex_unlock(&param.mutex);
    while (!result) {
        noecho();

        moznost = wgetch(window);
//        log_debug("CYKLUS menuLobby");

        pthread_mutex_lock(&param.mutex);
        result = param.resultLobby;
        param.choice = moznost;
        pthread_mutex_unlock(&param.mutex);
    }

    echo();
    param = paramEmpty;
    pthread_exit(0);
}

/**
 * Funkcia vypise Lobby pre vytvorenu hru
 * @param my_window - okno v ktorom sa maju vykreslit informacie o hre
 * @param startY - index od ktoreho ma zacinat okno na Y osi
 * @param startX - index od ktoreho ma zacinat okno na X osi
 * @return - vracia volbu od uzivatela ci si praje spustit hru alebo hru opustit
 */
int menuLobby(WINDOW *my_window, int startY, int startX) {
    //TODO doplnit do lobby informacie o hre a hracoch (nazov lobby, pocet hracov, kto je admin)
    wclear(my_window);

    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LOBBY --> Name: %s   Id: %d   Players: %d\n", game.nazovHry, game.gameId,
              game.pocetHracov);
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);

    const char *choices[2];
    choices[0] = "Start Game";
    choices[1] = "Leave Game";
//TODO  START GAME LEN PRE ADMINA - malo by byt hotove ale treba otestovat
    int highlight = 0;

    param.mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&param.mutex);
    param.lobby_Win = newwin(LOBBY_WIN_SIZE, WIN_WIDTH, startY + WIN_HEIGHT, startX);
    keypad(param.lobby_Win, true);
    wclear(param.lobby_Win);
    param.resultLobby = false;
    pthread_mutex_unlock(&param.mutex);

    pthread_t userInputThread;
    pthread_create(&userInputThread, NULL, handleUserInput, NULL);
    char data[BUFFER_SIZE];
    int count = 0;
    sprintf(data, "%d %d", count, game.gameId);
    communication(GET_LOBBY_PLAYER, data);
    int i = 0;
    while (1) {
        if (game.admin == true) {
            for (int i = 0; i < 2; i++) {
                if (i == highlight) {
                    wattron(param.lobby_Win, A_REVERSE);
                }
                mvwprintw(param.lobby_Win, i + 1, 1, choices[i]);
                wattroff(param.lobby_Win, A_REVERSE);
            }
        } else {
            highlight = 1;
            for (int i = 1; i < 2; i++) {
                if (i == highlight) {
                    wattron(param.lobby_Win, A_REVERSE);
                }
                mvwprintw(param.lobby_Win, i + 1, 1, choices[i]);
                wattroff(param.lobby_Win, A_REVERSE);
            }
        }

        if (socketReady()) {
            int pomT, pomR;
            sscanf(dataFromRequest(), "%d %d", &pomT, &pomR);

            if ((enum communication_type) pomT == JOIN_LOBBY && (enum communication_type) pomR == CREATED) {
                game.pocetHracov++;
                sscanf(dataFromRequest(), "%d %d %d %s", &pomT, &pomR,
                       &game.users[game.pocetHracov].id,
                       game.users[game.pocetHracov].name);
                game.users[count].amI = false;
                mvwprintw(my_window, i + 6, 1, "%s", game.users[game.pocetHracov].name);
                i++;
            }
//            log_debug("Count player %d   POcet %d", count, game.pocetHracov);

            if ((enum communication_type) pomT == GET_LOBBY_PLAYER && (enum communication_type) pomR != DONE) {
                sscanf(dataFromRequest(), "%d %d %d %s", &pomT, &pomR,
                       &game.users[count].id,
                       game.users[count].name);
                game.users[count].amI = false;
//                log_debug("GET LOBBBY PLAYER EVENT Count player %d   POcet %d", count, game.pocetHracov);
                mvwprintw(my_window, i + 6, 1, "%s", game.users[count].name);
                i++;
                count++;
                sprintf(data, "%d %d", count, game.gameId);
                communication(GET_LOBBY_PLAYER, data);
            }

            if ((enum communication_type) pomT == LEAVE_LOBBY && (enum communication_type) pomR == OKEJ) {
                int admin;
                sscanf(dataFromRequest(), "%d %d %d", &pomT, &pomT, &admin);
                if (admin) {
                    lobbyChoice(&param, &userInputThread);
                    highlight = 1;
                    game = emptyGame;
                    return highlight;
                }


//                log_debug(" LEAVe LOBBY EVENT Count player %d   POcet %d", count, game.pocetHracov);

                game.pocetHracov--;
                i = 0;
                count = 0;
                for (int j = 0; j < 4; ++j) {
                    mvwprintw(my_window, j + 6, 1, "%s", "                                                       ");
                }
                sprintf(data, "%d %d", count, game.gameId);
                communication(GET_LOBBY_PLAYER, data);

            }

            if ((enum communication_type) pomT == START && (enum communication_type) pomR == OKEJ) {

                startGame();

            }
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
                if (game.admin == true) {
                    if (highlight == 2)
                        highlight = 1;
                } else {
                    if (highlight == 1)
                        highlight = 0;
                }
                break;
            case ENTER:
                lobbyChoice(&param, &userInputThread);
                return highlight;
            default:
                break;
        }
        wrefresh(my_window);
        wrefresh(param.lobby_Win);
        usleep(30);
    }
}


int lobbyChoice(CHOICE *param, pthread_t *thread) {
    pthread_mutex_lock(&param->mutex);
    wclear(param->lobby_Win);
    wclear(my_window);
    wrefresh(param->lobby_Win);
    wrefresh(my_window);
    delwin(param->lobby_Win);
    param->resultLobby = true;
    pthread_mutex_unlock(&param->mutex);
//    pthread_join(*thread, NULL);
    pthread_mutex_destroy(&param->mutex);
}


/**
 * Funkciu vyuziva vlakno, ktore caka na vstup od uzivatela.
 * Ak uzivatel stlaci ESC tak sa vrati do mainMenu inak sa moze pohybovat
 * sipkami po dostupnych hrach a vybrat si do ktorej sa chce pripojit pomocou stlacenia ENTER
 * @param param - struktura, ktora obsahuje informacie o vstupe od uzivatela
 */
void *handleEsc() {
    int value;
    pthread_mutex_lock(&param.mutex);
    _Bool result = param.resultFindeGame;
    WINDOW *window = param.lobby_Win;
    pthread_mutex_unlock(&param.mutex);
    while (!result) {
        noecho();
        value = wgetch(window);
//        log_debug("cyklus FINDserver");
        pthread_mutex_lock(&param.mutex);
        result = param.resultFindeGame;
        param.choice = value;
        pthread_mutex_unlock(&param.mutex);
    }
    echo();
    param = paramEmpty;
    pthread_exit(0);
}

/**
 * Funkcia sluzi na vypisanie dostupnych (vytvorenych) hier, do ktorych sa môze
 * uzivatel prihlasit.
 * @param my_window - okno v ktorom sa ma vykreslit obsah
 */
int menuFindServer(WINDOW *my_window) {
//    CHOICE param;
    pthread_t userInputThread;
    pthread_create(&userInputThread, NULL, handleEsc, NULL);
    param.mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&param.mutex);
    param.lobby_Win = my_window;
    keypad(param.lobby_Win, true);
    wclear(param.lobby_Win);
    param.resultFindeGame = false;
    pthread_mutex_unlock(&param.mutex);

    wclear(my_window);
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "FINDING GAME\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    wrefresh(my_window);
    int count = 0;
    char data[BUFFER_SIZE];
    sprintf(data, "%d", count);
    communication(FIND_SERVERS, data);
    int highlight = 0;

    struct game *arrayOfGameId = malloc(sizeof(struct game));
    struct game *pomPointerArray = arrayOfGameId;
    while (1) {
        if (socketReady()) {
            if (resultFromRequest() != DONE) {
                int pom;
//                char name[GAME_NAME_LENGTH];
                sscanf(dataFromRequest(), "%d %d %d %s %d %d %d", &pom, &pom, &arrayOfGameId->gameId,
                       arrayOfGameId->nazovHry, &arrayOfGameId->cisloMapy,
                       &arrayOfGameId->maxPocetHracov, &pom);
                count++;
                pomPointerArray = (struct game *) realloc(pomPointerArray, ((count + 1) * sizeof(struct game)));
                arrayOfGameId++;
//                log_debug("%s", dataFromRequest());
                sprintf(data, "%d", count);
                communication(FIND_SERVERS, data);
            } else {
            }
//            wrefresh(my_window);
        }


        for (int i = 0; i < count; i++) {
            if (i == highlight)
                wattron(param.lobby_Win, A_REVERSE);
            mvwprintw(param.lobby_Win, i + 6, 1, "Id: %d    MAX Player: %d  Map Number: %d  Name: %s\n",
                      pomPointerArray[i].gameId, pomPointerArray[i].maxPocetHracov, pomPointerArray[i].cisloMapy,
                      pomPointerArray[i].nazovHry);
            wattroff(param.lobby_Win, A_REVERSE);
        }
        pthread_mutex_lock(&param.mutex);
        int choice = param.choice;
        param.choice = RESET_CHOICE;
        pthread_mutex_unlock(&param.mutex);
        int ch = 0;
//        log_debug("Count %d", count);
//        log_debug("");
//        sleep(2);
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == count)
                    highlight = count - 1;
                break;
            case ENTER:
                sprintf(data, "%d", pomPointerArray[highlight].gameId);
                enum result_code result = communication(JOIN_LOBBY, data);
                switch (result) {
                    case OKEJ:
                        sscanf(dataFromRequest(), "%d %d %d %s %d %d %d", &game.pocetHracov, &game.pocetHracov,
                               &game.gameId, game.nazovHry, &game.cisloMapy, &game.pocetHracov,
                               &game.maxPocetHracov);
                        game.users[game.pocetHracov] = user;
                        game.users[game.pocetHracov].amI = true;
                        game.admin = false;
                        game.pocetHracov++;
                        log_debug("");
                        finishChoice(&param, &userInputThread, pomPointerArray);
                        return JOIN;
                    case SERVICE_UNAVAILABLE:
                        //TODO full lobby
                        wclear(my_window);
                        mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
                        mvwprintw(my_window, 3, 10, "FINDING GAME\n");
                        mvwprintw(my_window, 4, 1,
                                  "_________________________________________________________________________________________\n");
                        mvwprintw(my_window, 7, 5, "Lobby je PLNE! Neda sa prihlasit do Hry. \n");
                        wrefresh(my_window);
                        finishChoice(&param, &userInputThread, pomPointerArray);
                        sleep(1);
                        return ESC;
                    case NOT_FOUND:
                        //TODO not FOund
                        wclear(my_window);
                        mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
                        mvwprintw(my_window, 3, 10, "FINDING GAME\n");
                        mvwprintw(my_window, 4, 1,
                                  "_________________________________________________________________________________________\n");
                        mvwprintw(my_window, 7, 5, "Nie su dostupne ziadne hry! \n");
                        wrefresh(my_window);
                        finishChoice(&param, &userInputThread, pomPointerArray);
                        sleep(1);
                        return ESC;
                    default:
                        break;
                }
                break;
            case ESC:
                finishChoice(&param, &userInputThread, pomPointerArray);
//                sleep(1);
//                pthread_mutex_lock(&param.mutex);
//                param.result = true;
//                pthread_mutex_unlock(&param.mutex);
                return ESC;
            default:
                break;
        }
        wrefresh(param.lobby_Win);
        wrefresh(my_window);
        usleep(30);
    }
}

void finishChoice(CHOICE *param, pthread_t *thread, struct game *lobbyGameArray) {
    pthread_mutex_lock(&param->mutex);
    param->resultFindeGame = true;
    pthread_mutex_unlock(&param->mutex);
//    pthread_join(*thread, NULL);
    pthread_mutex_destroy(&param->mutex);
    free(lobbyGameArray);
}

/**
 * Funkcia sluzi na vypis jednotlivych statistik.
 * @param my_window - okno v ktorom sa ma vypisat obsah.
 */
void menuLeaderBoard(WINDOW *my_window) {
    wclear(my_window);
    mvwprintw(my_window, 1, 40, "BOMBERMAN\n");
    mvwprintw(my_window, 3, 10, "LEADER BOARD\n");
    mvwprintw(my_window, 4, 1,
              "_________________________________________________________________________________________\n");
    mvwprintw(my_window, 6, 1, "Name\t| Wins\t| Loses\t| Kills\t| Deaths | Played Games");
    wrefresh(my_window);
    //TODO Treba vytvoriť funkciu pre vypis statistiky z databazy
    //TODO dorobiť nove okno s moznostami vyberu zoradenia statistiky
    wrefresh(my_window);
}

/**
 * Funkcia vypise do okna uvodne menu pre hru BOMBERMAN
 * @param my_window - okno v ktorom sa ma vykreslit obsah
 * @return - vracia hodnotu (volbu) ktoru si zvolil uzivatel
 */
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
            case ENTER:
                return highlight;
            default:
                break;
        }
    }
}

void closeMenu() {
    delwin(my_window);
}