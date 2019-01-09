#include "mapa.h"
#include "../Menu/menu.h"


void zmenavMape(int py,int px,int c){
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
    //hra.hraci[1].smer=0;
    hra.mapa.velkost[(py)][(px)] = (char)c;
    pthread_mutex_unlock(hra.mapa.mutex);
}

/**
 * Funckia na zistenie velkosti mapy
 * @param - nazov suboru, kde je mapa
 */
void zistiVelkostMapy(char *menoMapy){
    FILE *file;
    log_debug("Meno mapy pre zistenie %s", menoMapy);
    file = fopen(menoMapy, "r");

    if (NULL == file) {
        printf("Error opening file");
        sleep(1);
        exit(EXIT_FAILURE);
    }

    int c;

    hra.mapa.x=0;
    hra.mapa.y=0;
    while ((c = fgetc(file)) != EOF)
    {
        hra.mapa.x++;
        if(c=='\n')
        {
            hra.mapa.y++;
        }
    }
    fclose(file);
};

/**
 * Funkcia na otvorenie subora kde sa nachadza mapa a nasledne funkcia alokuje miesto pre mapu a nacita ju
 * @param mapa je struktura mapy
 * @param menoMapy nazov subora kde sa nachadza mapa
 */
void nacitajMapu(char *menoMapy){

    FILE * subor;
    subor = fopen(menoMapy, "r");

//   mapa->x=((mapa->x)/(mapa->y+1))*4+1;
//   mapa->y=(mapa->y+1)*2;

    hra.mapa.x=(hra.mapa.x)/(hra.mapa.y+1)+1;
    hra.mapa.y=(hra.mapa.y+1);
    //printf("%d %d ",mapa->x,mapa->y);
    //log_debug("x:%d y:%d ",mapa->x,mapa->y);
    int px = 0, py = 0;
    hra.mapa.velkost = createM(hra.mapa.y,hra.mapa.x);
    int c;

    while ((c = fgetc(subor)) != EOF)
    {
        zmenavMape(py,px,(char)c);
        px++;
        if(c == '\n'){
            py++;
            px=0;
        }
    }
    //log_debug("x:%d y:%d ",mapa->x,mapa->y);
    fclose(subor);
}

/**
 * Funkcia na vykreslenie mapy
 * @param mapa
 */
//TODO treba zmenit format ncurses
void  vykresliMapu(){
    char pom[1];
    for (int y = 0; y < hra.mapa.y; y++) {
        for (int x = 0; x < hra.mapa.x; x++) {
            pom[0] = hra.mapa.velkost[y][x];
            // mvprintw(y+1,x+1,&pom[0]);
//            mvprintw((y * 2), (x * 4), &pom[0]);
//            mvprintw((y * 2), (x * 4) + 1, &pom[0]);
//            mvprintw((y * 2), (x * 4) + 2, &pom[0]);
//            mvprintw((y * 2), (x * 4) + 3, &pom[0]);

            mvwprintw(mapWindow,(y * 2), (x * 4), &pom[0]);
            mvwprintw(mapWindow,(y * 2), (x * 4) + 1, &pom[0]);
            mvwprintw(mapWindow,(y * 2), (x * 4) + 2, &pom[0]);
            mvwprintw(mapWindow,(y * 2), (x * 4) + 3, &pom[0]);

            mvwprintw(mapWindow,(y * 2) + 1, (x * 4), &pom[0]);
            mvwprintw(mapWindow,(y * 2) + 1, (x * 4) + 1, &pom[0]);
            mvwprintw(mapWindow,(y * 2) + 1, (x * 4) + 2, &pom[0]);
            mvwprintw(mapWindow,(y * 2) + 1, (x * 4) + 3, &pom[0]);

//            mvprintw((y * 2) + 1, (x * 4), &pom[0]);
//            mvprintw((y * 2) + 1, (x * 4) + 1, &pom[0]);
//            mvprintw((y * 2) + 1, (x * 4) + 2, &pom[0]);
//            mvprintw((y * 2) + 1, (x * 4) + 3, &pom[0]);
            wrefresh(mapWindow);
        }
    }
}

void initMap(int cisloMapy){
    char menoMapy[20];
    sprintf(menoMapy, "%s%d", "../Mapy/", cisloMapy);
    strcat(menoMapy, ".txt");

    log_debug("Meno mapy %s", menoMapy);
    sleep(2);

    zistiVelkostMapy(menoMapy);
    log_debug("Viem velkost mapy X=%d -- Y=%d", hra.mapa.x, hra.mapa.y);
    nacitajMapu(menoMapy);
    log_debug("Mam nacitanu mapu Velkost=%d", hra.mapa.velkost);

    //WINDOW *map_Window;

    initscr();
    cbreak();
    int startX = 0, startY = 0;

    refresh();
    mapWindow = newwin(hra.mapa.y, hra.mapa.x, startY, startX);
    keypad(mapWindow, true);

    log_debug("Vykreslujem mapu");
    vykresliMapu();
    sleep(10);
}
