#include "mapa.h"
#include "../Menu/menu.h"


void zmenavMape(int py, int px, char c) {
//    mapa->velkost[(py*2)][(px*4)] = (char)c;
//    mapa->velkost[(py*2)][(px*4)+1] = (char)c;
//    mapa->velkost[(py*2)][(px*4)+2] = (char)c;
//    mapa->velkost[(py*2)][(px*4)+3] = (char)c;
//
//    mapa->velkost[(py*2)+1][(px*4)] = (char)c;
//    mapa->velkost[(py*2)+1][(px*4)+1] = (char)c;
//    mapa->velkost[(py*2)+1][(px*4)+2] = (char)c;
//    mapa->velkost[(py*2)+1][(px*4)+3] = (char)c;
    pthread_mutex_lock(hra.mapa.mutex);
    hra.mapa.velkost[(py)][(px)] = c;
    pthread_mutex_unlock(hra.mapa.mutex);
}

/**
 * Funckia na zistenie velkosti mapy
 * @param - nazov suboru, kde je mapa
 */
void zistiVelkostMapy(char *menoMapy) {
    FILE *file;
//    log_debug("Meno mapy pre zistenie %s", menoMapy);
    file = fopen(menoMapy, "r");

    if (NULL == file) {
        log_debug("Nepodarilo sa otvorit subor.");
        printf("Error opening file");
        sleep(1);
        exit(EXIT_FAILURE);
    }

    int c;

    hra.mapa.x = 0;
    hra.mapa.y = 0;
    while ((c = fgetc(file)) != EOF) {
//        log_debug("C -- %d", c);
        hra.mapa.x++;
//        log_debug("X - %d", hra.mapa.x);
        if (c == '\n') {
            hra.mapa.y++;
//            log_debug("Y - %d", hra.mapa.y);
        }
    }
    fclose(file);
//    log_debug("Zavrel som subor %s", menoMapy);
};

/**
 * Funkcia na otvorenie subora kde sa nachadza mapa a nasledne funkcia alokuje miesto pre mapu a nacita ju
 * @param mapa je struktura mapy
 * @param menoMapy nazov subora kde sa nachadza mapa
 */
void nacitajMapu(char *menoMapy) {

    FILE *subor;
    int px = 0, py = 0, c = 0;

    hra.mapa.x = (hra.mapa.x) / (hra.mapa.y + 1) + 1;
    hra.mapa.y = (hra.mapa.y + 1);
    hra.mapa.velkost = createM(hra.mapa.y, hra.mapa.x);

    subor = fopen(menoMapy, "r");

    if (subor == NULL) {
        log_debug("Nepodarilo sa otvorit subor.");
        exit(EXIT_FAILURE);
    }

    while ((c = fgetc(subor)) != EOF) {
        zmenavMape(py, px, (char) c);
        px++;
        if (c == '\n') {
            py++;
            px = 0;
        }
    }
//    log_debug("zatvaram subor %d", fclose(subor));
    //log_debug("x:%d y:%d ",mapa->x,mapa->y);
//    fclose(subor);
}


/**
 * Funkcia na vykreslenie mapy
 * @param mapa
 */
void vykresliMapu() {
    char pom[1];
    for (int y = 0; y < hra.mapa.y; y++) {
        for (int x = 0; x < hra.mapa.x; x++) {
            pom[0] = hra.mapa.velkost[y][x];

            switch (pom[0]) {
                case WALL:
                    wattron(mapWindow, COLOR_PAIR(WALL_PAIR));
                    printElement(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(WALL_PAIR));
                    break;

                case EMPTY:
                    wattron(mapWindow, COLOR_PAIR(EMPTY_PAIR));
                    printElement(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(EMPTY_PAIR));
                    break;
                case BARRIER:
                    wattron(mapWindow, COLOR_PAIR(WALL_DESTROY_PAIR));
                    printElement(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(WALL_DESTROY_PAIR));
                    break;
                case PLAYER_ONE:
                    wattron(mapWindow, COLOR_PAIR(PLAYER_ONE_PAIR));
                    printPlayer(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(PLAYER_ONE_PAIR));
                    break;
                case PLAYER_TWO:
                    wattron(mapWindow, COLOR_PAIR(PLAYER_TWO_PAIR));
                    printPlayer(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(PLAYER_TWO_PAIR));
                    break;
                case PLAYER_THREE:
                    wattron(mapWindow, COLOR_PAIR(PLAYER_THREE_PAIR));
                    printPlayer(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(PLAYER_THREE_PAIR));
                    break;
                case PLAYER_FOUR:
                    wattron(mapWindow, COLOR_PAIR(PLAYER_FOUR_PAIR));
                    printPlayer(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(PLAYER_FOUR_PAIR));
                    break;
                case BOMB_THREE:
                    wattron(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    printElement(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    break;
                case BOMB_TWO:
                    wattron(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    printElement(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    break;
                case BOMB_ONE:
                    wattron(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    printElement(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    break;
                case BOMB_BOOM:
                    wattron(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    printElement(y, x, pom[0]);
                    wattroff(mapWindow, COLOR_PAIR(BOMB_PAIR));
                    break;
                default:
                    break;
            }
            wrefresh(mapWindow);
        }
    }
//    wrefresh(mapWindow);
}

/**
 * Funkcia nainicializuje farby + okno pre hru, vytvorí okno a vypiše mapu
 * @param cisloMapy - cislo mapy
 */
void initMap(int cisloMapy, int pocetHracou, int index) {
    char menoMapy[20];
    sprintf(menoMapy, "%s%d", "../Mapy/", cisloMapy);
    strcat(menoMapy, ".txt");
    refresh();
    if (has_colors() == FALSE) {
        log_debug("Konzola/terminal nepodporuje farby!");
        exit(EXIT_FAILURE);
    }
    start_color();
    initColor();

    initGame(pocetHracou, menoMapy, index);
}

/**
 * Funkcia vytvori farebne pary pre pismo a jeho pozadie
 */
void initColor() {
    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_WHITE);
    init_pair(EMPTY_PAIR, COLOR_BLACK, COLOR_BLACK);
    init_pair(WALL_DESTROY_PAIR, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(PLAYER_ONE_PAIR, COLOR_GREEN, COLOR_GREEN);
    init_pair(PLAYER_TWO_PAIR, COLOR_BLUE, COLOR_BLUE);
    init_pair(PLAYER_THREE_PAIR, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(PLAYER_FOUR_PAIR, COLOR_CYAN, COLOR_CYAN);
    init_pair(BOMB_PAIR, COLOR_WHITE, COLOR_RED);
};

/**
 * Funkcia vykresli znak do mapy (nacita sa jeden znak zo suboru a vykresli sa ako 4x4)
 * @param y
 * @param x
 * @param indicator
 */
void printElement(int y, int x, char indicator) {
    char pom[1];
    pom[0] = indicator;

    mvwprintw(mapWindow, (y * 2), (x * 4), "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2), (x * 4) + 1, "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2), (x * 4) + 2, "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2), (x * 4) + 3, "%c", pom[0]);

    mvwprintw(mapWindow, (y * 2) + 1, (x * 4), "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2) + 1, (x * 4) + 1, "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2) + 1, (x * 4) + 2, "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2) + 1, (x * 4) + 3, "%c", pom[0]);
}

/**
 * FUnkcia vykresli hraca do mapy
 */
void printPlayer(int y, int x, char indicator) {
    char pom[1];
    pom[0] = indicator;


    mvwprintw(mapWindow, (y * 2), (x * 4) + 1, "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2), (x * 4) + 2, "%c", pom[0]);

    mvwprintw(mapWindow, (y * 2) + 1, (x * 4) + 1, "%c", pom[0]);
    mvwprintw(mapWindow, (y * 2) + 1, (x * 4) + 2, "%c", pom[0]);
}
