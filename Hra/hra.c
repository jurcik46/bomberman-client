////
//// Created by sterb on 9. 1. 2019.
////
//#include "hra.h"
//
///**
// * Funkcia allokuje pamät pre mapu
// * @param m - pocet riadkov
// * @param n - pocet stlpcov
// * @return - vrati smernik na prvy prvok pola
// */
//char** createM(int m, int n) {
//    char **mat;
//    mat = malloc(m * sizeof (*mat));
//    for (int i = 0; i < m; i++) {
//        mat[i] = calloc(n, sizeof (char));
//    }
//    return mat;
//}
///**
// * Uvolnenie pamete pre mapu
// * @param m
// * @param mat
// */
//void deletM(int m, char ***mat) {
//    for (int i = 0; i < m; i++) {
//        free((*mat)[i]);
//    }
//    free((*mat));
//    *mat = NULL;
//}
//
//void pohybHraca(HRAC * hrac) {
////log_debug("som v pohybHraca");
//
//    switch (hrac->smer) {
//        case 'a':
//            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position-1] == ' ') {
//                if(hra.mapa.velkost[hrac->y_Position][hrac->x_Position]== hrac->znak)
//                    zmenavMape(hrac->y_Position, hrac->x_Position,  ' ');
//                hrac->x_Position= (hrac->x_Position-1);
//
//                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
//
//                hrac->smer = 0;
//            }
//            break;
//        case 'w':
//            hrac->smer = 0;
//            if (hra.mapa.velkost[hrac->y_Position-1][hrac->x_Position] ==  ' ') {
//                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
//                    zmenavMape(hrac->y_Position, hrac->x_Position,  ' ');
//                hrac->y_Position--;
//
//                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
//            }
//            break;
//        case 's':
//            hrac->smer = 0;
//            if (hra.mapa.velkost[hrac->y_Position+1][hrac->x_Position] ==  ' ') {
//                if(hra.mapa.velkost[hrac->y_Position][hrac->x_Position]== hrac->znak)
//                    zmenavMape(hrac->y_Position, hrac->x_Position,  ' ');
//                hrac->y_Position++;
//
//                zmenavMape( hrac->y_Position, hrac->x_Position, hrac->znak);
//            }
//            break;
//        case 'd':
//            hrac->smer =0;
//            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position+1] == Prazdne) {
//                if(hra.mapa.velkost[hrac->y_Position][hrac->x_Position]== hrac->znak) {
//                    zmenavMape( hrac->y_Position, hrac->x_Position, Prazdne);
//                }
//                hrac->x_Position++;
//                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
//                ;
//            }
//            break;
//        case ' ':
//            //todo zistim ktora bomba je volna
//            hrac->smer=0;
//            vytvorBombu(hrac,1);
//            break;
//        default:
//
//            break;
//    }
//}
//
///**
// * Funkcia zistuje ci bolo nieco stlacene
// * @param input
// * @return
// */
//void *delay(void * hrac) {
//    do {
//        hra.hraci[((HRAC*)hrac)->IDhraca].smer = getchar();
//    } while (1);
//}
//
//

//
// Created by Phixell on 6. 1. 2019.
//

#include "hra.h"


char **createM(int m, int n) {
    char **mat;
    mat = malloc(m * sizeof(*mat));
    for (int i = 0; i < m; i++) {
        mat[i] = calloc(n, sizeof(char));
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
 * Funkcia na zistenie ci hrac behol do bomby a nasledne vykreslenie
 * @param hrac
 * @return
 */
int trafilSomVBombuHracaID(HRAC *hrac) {
//    log_debug("som vo funckii trailbombuhracaID");
//    log_debug("%d,", hra.mapa.velkost[hrac->y_Position][hrac->x_Position]);
    if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == Vybuch) {
        for (int a = 0; a < POCET_HRACOV; a++) {
            for (int b = 0; b < MAX_POCETBOMB; b++) {
                if (hra.hraci[a].bomba[b].zijeBomba == 1) {
                    if ((hra.hraci[a].bomba[b].x_Position == hra.hraci[a].x_Position) &&
                        (hra.hraci[a].bomba[b].y_Position == hra.hraci[a].y_Position)) {
                        return hra.hraci[a].bomba[b].idHRACABOMBY;
                    }
                }
            }
        }
    }
}

//todo rozdelit do funckii pohyb

void pohybHraca(HRAC *hrac) {
//    log_debug("HRAC1: %d",hrac->smer);

    switch (hrac->smer) {
        case 'a':

            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position - 1] == ' ') {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                    zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                hrac->x_Position = (hrac->x_Position - 1);

                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);

                hrac->smer = 0;
            }
            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position - 1] == Vybuch) {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                    zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                hrac->pocetZivotov--;
                hrac->statistikahracavhre.pocetUmrti++;
                hrac->x_Position--;
                hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);

            }
            break;
        case 'w':
            hrac->smer = 0;
            if (hra.mapa.velkost[hrac->y_Position - 1][hrac->x_Position] == ' ') {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                    zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                hrac->y_Position--;

                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
            }
            if (hra.mapa.velkost[hrac->y_Position - 1][hrac->x_Position] == Vybuch) {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                    zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                hrac->pocetZivotov--;
                hrac->statistikahracavhre.pocetUmrti++;
                hrac->y_Position--;
                hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);

            }
            break;
        case 's':
            hrac->smer = 0;
            if (hra.mapa.velkost[hrac->y_Position + 1][hrac->x_Position] == ' ') {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                    zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                hrac->y_Position++;

                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
            }
            if (hra.mapa.velkost[hrac->y_Position + 1][hrac->x_Position] == Vybuch) {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                    zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                hrac->pocetZivotov--;
                hrac->statistikahracavhre.pocetUmrti++;
                hrac->y_Position++;
                hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);

            }
            break;
        case 'd':
            hrac->smer = 0;
            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position + 1] == Prazdne) {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak) {
                    zmenavMape(hrac->y_Position, hrac->x_Position, Prazdne);
                }
                hrac->x_Position++;
                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);;
            }
            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position + 1] == Vybuch) {
                if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                    zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                hrac->pocetZivotov--;
                hrac->statistikahracavhre.pocetUmrti++;
                hrac->x_Position++;
                hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);

            }
            break;
        case ' ':
//            log_debug("som v MEDZERE");
            hrac->smer = 0;

            int bombanavytvorenie = MAX_POCETBOMB;
            for (int b = 0; b < MAX_POCETBOMB; b++) {
//                log_debug("Bomba cislo:%d stav:%d", b, hrac->bomba[b].zijeBomba);
                if (hrac->bomba[b].zijeBomba == 0) {

                    bombanavytvorenie = b;
                }
            }
            if (bombanavytvorenie >= 0 && bombanavytvorenie < MAX_POCETBOMB) {
//                log_debug("Vytvaram bombu: %d", bombanavytvorenie);
                vytvorBombu(hrac, bombanavytvorenie);
                hrac->bomba[bombanavytvorenie].zijeBomba = 1;
                hrac->statistikahracavhre.pocetUlozenychBomb++;
            }
            break;
        default:
            break;
    }
}

/**
 * Funkcia zistuje ci bolo nieco stlacene
 * @param input
 * @return
 */

void *delay(void *hrac) {
    do {
//        log_debug("DELAY1");
        hra.hraci[((HRAC *) hrac)->IDhraca].smer = getchar();
    } while (1);

}

/**
 * Funkcia vytvori bombu a alokuje pre nu miesto a nastavi ju do mapy
 * @param mapa
 * @param hrac
 */

void vytvorBombu(HRAC *hrac, int cisloBomby) {
    hra.hraci[hrac->IDhraca].bomba[cisloBomby].y_Position = hrac->y_Position;
    hra.hraci[hrac->IDhraca].bomba[cisloBomby].x_Position = hrac->x_Position;
    hra.hraci[hrac->IDhraca].bomba[cisloBomby].znak = '*';
    hra.hraci[hrac->IDhraca].bomba[cisloBomby].idHRACABOMBY = hrac->IDhraca;

    //zmenavMape(hrac->bomba->y_Position,hrac->bomba->x_Position,hrac->bomba->znak);

    // vytvorVlaknoPreBombu(odpocetBomby,&hra.hraci[hrac->IDhraca].bomba[cisloBomby-1]);
    pthread_t vlakno;
    pthread_create(&vlakno, 0, &odpocetBomby, &hrac->bomba[cisloBomby]);
}


void *odpocetBomby(void *bomba) {
//    log_debug("y:%d x:%d",hra.hraci[((struct bomba*)bomba)->idHRACABOMBY].bomba[0].y_Position,hra.hraci[((struct bomba*)bomba)->idHRACABOMBY].bomba[0].x_Position);
    //log_debug("som v odpovec BOMBY:%d", );
    for (int a = NUMBER_THREE; a > NUMBER_ZERO; a--) {

        zmenavMape(((struct bomba *) bomba)->y_Position, ((struct bomba *) bomba)->x_Position, (char) a);
//        ((struct bomba*)bomba)->cas=a;
        sleep(1);
    }
    vybuchBomby(((struct bomba *) bomba));

    pthread_exit(0);
}

/**
 * Funkcia na vytvorenie vlakna pre bombu
 * @param startovaciaFunkcia
 * @param mapa
 * @param hrac
 */

void vybuchBomby(BOMBA *bomba) {
    int dole = 0;
    int hore = 0;
    int vlavo = 0;
    int vpravo = 0;
    //zistenie kam moze vybuchnut bomba
    if (hra.mapa.velkost[bomba->y_Position + 1][bomba->x_Position] != Stena)dole = +1;
    if (hra.mapa.velkost[bomba->y_Position - 1][bomba->x_Position] != Stena)hore = -1;
    if (hra.mapa.velkost[bomba->y_Position][bomba->x_Position + 1] != Stena)vpravo = +1;
    if (hra.mapa.velkost[bomba->y_Position][bomba->x_Position - 1] != Stena)vlavo = -1;

    BOOM(bomba, dole, hore, vlavo, vpravo);
    //sleep(1);

    bomba->zijeBomba = 0;
    //vymazanieBombyZObrazovky(bomba, dole, hore, vlavo, vpravo);
    //vratenie hraca na poziciu



    //hra.hraci[bomba.idHRACABOMBY].bomba[];
    //bomba->zijeBomba=0;
}

void BOOM(BOMBA *bomba, int dole, int hore, int vlavo, int vpravo) {
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
    if (hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position] == PLAYER_ONE ||
        hra.mapa.velkost[bomba->y_Position + hore][bomba->x_Position] == PLAYER_ONE ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position + vpravo] == PLAYER_ONE ||
        hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position + vlavo] == PLAYER_ONE ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position] == PLAYER_ONE) {
        hra.hraci[0].pocetZivotov--;
        hra.hraci[0].statistikahracavhre.pocetUmrti++;
        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a1 = 1;
    }
    if (hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position] == PLAYER_TWO ||
        hra.mapa.velkost[bomba->y_Position + hore][bomba->x_Position] == PLAYER_TWO ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position + vpravo] == PLAYER_TWO ||
        hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position + vlavo] == PLAYER_TWO ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position] == PLAYER_TWO) {
        hra.hraci[1].pocetZivotov--;
        hra.hraci[1].statistikahracavhre.pocetUmrti++;
        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a2 = 2;
    }

    if (hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position] == PLAYER_THREE ||
        hra.mapa.velkost[bomba->y_Position + hore][bomba->x_Position] == PLAYER_THREE ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position + vpravo] == PLAYER_THREE ||
        hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position + vlavo] == PLAYER_THREE ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position] == PLAYER_THREE) {
        hra.hraci[2].pocetZivotov--;
        hra.hraci[2].statistikahracavhre.pocetUmrti++;
        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a3 = 3;
    }

    if (hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position] == PLAYER_FOUR ||
        hra.mapa.velkost[bomba->y_Position + hore][bomba->x_Position] == PLAYER_FOUR ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position + vpravo] == PLAYER_FOUR ||
        hra.mapa.velkost[bomba->y_Position + dole][bomba->x_Position + vlavo] == PLAYER_FOUR ||
        hra.mapa.velkost[bomba->y_Position][bomba->x_Position] == PLAYER_FOUR) {
        hra.hraci[3].pocetZivotov--;
        hra.hraci[3].statistikahracavhre.pocetUmrti++;

        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a4 = 4;
    }
    zmenavMape(bomba->y_Position, bomba->x_Position, Vybuch);
    zmenavMape(bomba->y_Position + dole, bomba->x_Position, Vybuch);
    zmenavMape(bomba->y_Position + hore, bomba->x_Position, Vybuch);
    zmenavMape(bomba->y_Position, bomba->x_Position + vpravo, Vybuch);
    zmenavMape(bomba->y_Position, bomba->x_Position + vlavo, Vybuch);
    sleep(1);
    vymazanieBombyZObrazovky(bomba, dole, hore, vlavo, vpravo);
//    log_debug("----%d", a1);
    if (a1 == 1) {
//        log_debug("som TUUUUU");
        zmenavMape(hra.hraci[0].y_Position, hra.hraci[0].y_Position, hra.hraci[0].znak);

    }

}

void vymazanieBombyZObrazovky(BOMBA *bomba, int dole, int hore, int vlavo, int vpravo) {
    zmenavMape(bomba->y_Position, bomba->x_Position, Prazdne);
    zmenavMape(bomba->y_Position + dole, bomba->x_Position, Prazdne);
    zmenavMape(bomba->y_Position + hore, bomba->x_Position, Prazdne);
    zmenavMape(bomba->y_Position, bomba->x_Position + vpravo, Prazdne);
    zmenavMape(bomba->y_Position, bomba->x_Position + vlavo, Prazdne);

}

void printPlayersToScoreWindow() {
    int startY = 0;
    int startX = 1;

    for (int i = 0; i < hra.pocetHracov; i++) {
        mvwprintw(scoreWindow, startY + 1, startX, "%s", hra.hraci[i].statistikahracavhre.meno);
        startY++;
        mvwprintw(scoreWindow, startY + 1, startX, "Zivot: %d/3", hra.hraci[i].statistikahracavhre.pocetUmrti);
        startY++;
    }
    wrefresh(scoreWindow);
}

void initGame(int pocetHracov, char *cesta, int mojeID) {
    //Inicializacia okna

    //Nastavim pocetHracov;
    hra.pocetHracov = pocetHracov;

    //vytvorim mutex pre mapu
    pthread_mutex_t mutex_mapa;
    pthread_mutex_init(&mutex_mapa, NULL);

    //nastavim mutex pre mapu
    hra.mapa.mutex = &mutex_mapa;

    //zistim velkost mapy a nacitaj ju do pola
    zistiVelkostMapy(cesta);
    nacitajMapu(cesta);

    int startX = 0, startY = 0;
    //vytvorim okno pre mapu
    refresh();
    mapWindow = newwin(hra.mapa.y * 2, hra.mapa.x * 4, startY, startX);
    keypad(mapWindow, true);
    //vytvorim okno pre score
    refresh();
    scoreWindow = newwin(SCORE_WIN_Y, SCORE_WIN_X, startY, hra.mapa.x * 4);

    //TODO nacitaj  nove okno so statistikou

    // log_debug("Krok1");
    //funkcia na nastavenie pozici hracov
    for (int a = 0; a < pocetHracov; a++) {
        if (a == 0) {
            hra.hraci[a].x_Position = 1;
            hra.hraci[a].y_Position = 1;
            hra.hraci[a].znak = PLAYER_ONE;
            hra.hraci[a].pocetZivotov = 3;
            hra.hraci[a].IDhraca = 0;
            hra.hraci[a].cislo_bomby = 0;
            //inicializacia statistiky hry
            hra.hraci[a].statistikahracavhre.idHraca = a;
            hra.hraci[a].statistikahracavhre.pocetTrafenychHracov = 0;
            hra.hraci[a].statistikahracavhre.pocetUlozenychBomb = 0;
            hra.hraci[a].statistikahracavhre.pocetUmrti = 0;
//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, hra.hraci[a].znak);
        }
        if (a == 1) {
            hra.hraci[a].x_Position = hra.mapa.x - 3;
            hra.hraci[a].y_Position = 1;
            hra.hraci[a].znak = PLAYER_TWO;
            hra.hraci[a].pocetZivotov = 3;
            hra.hraci[a].IDhraca = 1;
            hra.hraci[a].cislo_bomby = 0;
            //inicializacia statistiky hry
            hra.hraci[a].statistikahracavhre.idHraca = a;
            hra.hraci[a].statistikahracavhre.pocetTrafenychHracov = 0;
            hra.hraci[a].statistikahracavhre.pocetUlozenychBomb = 0;
            hra.hraci[a].statistikahracavhre.pocetUmrti = 0;

//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, hra.hraci[a].znak);
        }
        if (a == 2) {
            hra.hraci[a].x_Position = 1;
            hra.hraci[a].y_Position = (hra.mapa.y - 3);
            hra.hraci[a].znak = PLAYER_THREE;
            hra.hraci[a].pocetZivotov = 3;
            hra.hraci[a].IDhraca = 2;
            hra.hraci[a].cislo_bomby = 0;
            //inicializacia statistiky hry
            hra.hraci[a].statistikahracavhre.idHraca = a;
            hra.hraci[a].statistikahracavhre.pocetTrafenychHracov = 0;
            hra.hraci[a].statistikahracavhre.pocetUlozenychBomb = 0;
            hra.hraci[a].statistikahracavhre.pocetUmrti = 0;
//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, hra.hraci[a].znak);
        }
        if (a == 3) {
            hra.hraci[a].x_Position = (hra.mapa.x - 3);
            hra.hraci[a].y_Position = (hra.mapa.y - 3);
            hra.hraci[a].znak = PLAYER_FOUR;
            hra.hraci[a].pocetZivotov = 3;
            hra.hraci[a].IDhraca = 3;
            hra.hraci[a].cislo_bomby = 0;
            //inicializacia statistiky hry
            hra.hraci[a].statistikahracavhre.idHraca = a;
            hra.hraci[a].statistikahracavhre.pocetTrafenychHracov = 0;
            hra.hraci[a].statistikahracavhre.pocetUlozenychBomb = 0;
            hra.hraci[a].statistikahracavhre.pocetUmrti = 0;
//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, hra.hraci[a].znak);
        }
//        vykresliMapu();
    }
//    log_debug("HRAC 1 -- %c", hra.hraci[0].znak);
//    log_debug("HRAC 2 -- %c", hra.hraci[1].znak);

    pthread_t vlakno2;
    pthread_create(&vlakno2, 0, &delay, &hra.hraci[mojeID]);

    while (1) {
        for (int a = 0; a < pocetHracov; a++) {
//            log_debug("Hrac_ID: %d Ulozena bomba:%dx Umrtia:%dx Trafenie_Hraca: %dx",
//                      hra.hraci[a].statistikahracavhre.idHraca,
//                      hra.hraci[a].statistikahracavhre.pocetUlozenychBomb, hra.hraci[a].statistikahracavhre.pocetUmrti,
//                      hra.hraci[a].statistikahracavhre.pocetTrafenychHracov);
        }
        //sleep(1);
        pohybHraca(&hra.hraci[mojeID]);
        vykresliMapu();
        printPlayersToScoreWindow();
    }
}


