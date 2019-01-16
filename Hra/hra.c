#include "hra.h"
#include "gameCommunication.h"

char data[50];

char **createM(int m, int n) {
    char **mat;
    mat = malloc(m * sizeof(*mat));
    for (int i = 0; i < m; i++) {
        mat[i] = calloc(n, sizeof(char));
    }
    log_debug("Alokoval som pamat");
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
    //log_debug("som vo funckii trafilbombuhracaID");

    //log_debug("%d,", hra.mapa.velkost[hrac->y_Position][hrac->x_Position]);
    if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == Vybuch) {
        for (int a = 0; a < POCET_HRACOV; a++) {
            for (int b = 0; b < MAX_POCETBOMB; b++) {
                if (hra.hraci[a].bomba[b].zijeBomba == 1) {
                    //log_debug("-1-");
                    if ((((hra.hraci[a].bomba[b].x_Position == hra.hraci[a].x_Position) &&
                          (hra.hraci[a].bomba[b].y_Position == hra.hraci[a].y_Position))) ||
                        (((hra.hraci[a].bomba[b].x_Position == hra.hraci[a].x_Position) &&
                          (hra.hraci[a].bomba[b].y_Position +
                           (hra.hraci[a].bomba[b].bombastrany.hore == hra.hraci[a].y_Position))) ||
                         ((hra.hraci[a].bomba[b].x_Position == hra.hraci[a].x_Position) &&
                          (hra.hraci[a].bomba[b].y_Position +
                           (hra.hraci[a].bomba[b].bombastrany.dole == hra.hraci[a].y_Position))) ||
                         (((hra.hraci[a].bomba[b].x_Position +
                            (hra.hraci[a].bomba[b].bombastrany.vlavo == hra.hraci[a].x_Position) &&
                            (hra.hraci[a].bomba[b].y_Position == hra.hraci[a].y_Position)))) ||
                         (((hra.hraci[a].bomba[b].x_Position +
                            (hra.hraci[a].bomba[b].bombastrany.vpravo == hra.hraci[a].x_Position) &&
                            (hra.hraci[a].bomba[b].y_Position == hra.hraci[a].y_Position)))))) {
                        return hra.hraci[a].bomba[b].idHRACABOMBY;
                    }
                }
            }
        }

    }
    return 0;
}

//todo rozdelit do funckii pohyb

void pohybHraca(HRAC *hrac) {
    //log_debug("HRAC1: %d", hrac->smer);
    if (hrac->mrtvy != 1)
        if (hrac->frezze == 0) {
            switch (hrac->smer) {
                case 'a':


                    if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position - 1] == ' ') {
                        if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                            zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                        hrac->x_Position--;
                        zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                        if (currentID == hrac->IDhraca) {
                            sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                            gameCommunication(SEND, data);
                        }

                        hrac->smer = 0;
                    }
                    if (hrac->smer != 0) {
                        if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position - 1] == Vybuch) {
                            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                                zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                            hrac->pocetZivotov--;
                            hrac->statistikahracavhre.pocetUmrti--;
                            hrac->x_Position--;
                            hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                            zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                            hrac->frezze = 1;
                            if (currentID == hrac->IDhraca) {
                                sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                                gameCommunication(SEND, data);
                            }
                            hrac->smer = 0;
                        }
                    }
                    break;
                case 'w':

                    if (hra.mapa.velkost[hrac->y_Position - 1][hrac->x_Position] == ' ') {
                        if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                            zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                        hrac->y_Position--;
                        zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                        if (currentID == hrac->IDhraca) {
                            sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                            gameCommunication(SEND, data);
                        }
                        hrac->smer = 0;

                    }
                    if (hrac->smer != 0) {
                        if (hra.mapa.velkost[hrac->y_Position - 1][hrac->x_Position] == Vybuch) {
                            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                                zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                            hrac->pocetZivotov--;
                            hrac->statistikahracavhre.pocetUmrti--;
                            hrac->y_Position--;
                            hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                            zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                            hrac->frezze = 1;
                            if (currentID == hrac->IDhraca) {
                                sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                                gameCommunication(SEND, data);
                            }
                            hrac->smer = 0;
                        }
                    }
                    break;
                case 's':

                    if (hra.mapa.velkost[hrac->y_Position + 1][hrac->x_Position] == ' ') {
                        if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                            zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                        hrac->y_Position++;

                        zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                        if (currentID == hrac->IDhraca) {
                            sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                            gameCommunication(SEND, data);
                        }
                        hrac->smer = 0;
                    }
                    if (hrac->smer != 0) {
                        if (hra.mapa.velkost[hrac->y_Position + 1][hrac->x_Position] == Vybuch) {
                            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                                zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                            hrac->pocetZivotov--;
                            hrac->statistikahracavhre.pocetUmrti--;
                            hrac->y_Position++;
                            hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                            zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                            hrac->frezze = 1;
                            if (currentID == hrac->IDhraca) {
                                sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                                gameCommunication(SEND, data);
                            }
                            hrac->smer = 0;
                        }
                    }
                    break;
                case 'd':

                    if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position + 1] == Prazdne) {
                        if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak) {
                            zmenavMape(hrac->y_Position, hrac->x_Position, Prazdne);
                        }
                        hrac->x_Position++;
                        zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                        if (currentID == hrac->IDhraca) {
                            sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                            gameCommunication(SEND, data);
                        }
                        hrac->smer = 0;

                    }
                    if (hrac->smer != 0) {
                        if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position + 1] == Vybuch) {
                            if (hra.mapa.velkost[hrac->y_Position][hrac->x_Position] == hrac->znak)
                                zmenavMape(hrac->y_Position, hrac->x_Position, ' ');
                            hrac->pocetZivotov--;
                            hrac->statistikahracavhre.pocetUmrti--;
                            hrac->x_Position++;
                            hra.hraci[trafilSomVBombuHracaID(hrac)].statistikahracavhre.pocetTrafenychHracov++;
                            zmenavMape(hrac->y_Position, hrac->x_Position, hrac->znak);
                            hrac->frezze = 1;
                            if (currentID == hrac->IDhraca) {
                                sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                                gameCommunication(SEND, data);
                            }
                            hrac->smer = 0;
                        }
                    }
                    break;
                case 'b':

                    //log_debug("som v MEDZERE");
                    hrac->smer = 'b';
                    int bombanavytvorenie = MAX_POCETBOMB;
                    for (int b = 0; b < MAX_POCETBOMB; b++) {
                        log_debug("Bomba cislo:%d stav:%d", b, hrac->bomba[b].zijeBomba);
                        if (hrac->bomba[b].zijeBomba == 0) {

                            bombanavytvorenie = b;
                        }

                    }
                    if (bombanavytvorenie >= 0 && bombanavytvorenie < MAX_POCETBOMB) {
                        log_debug("Vytvaram bombu: %d", bombanavytvorenie);
                        vytvorBombu(hrac, bombanavytvorenie);
                        hrac->bomba[bombanavytvorenie].zijeBomba = 1;
                        hrac->statistikahracavhre.pocetUlozenychBomb++;
                        if (currentID == hrac->IDhraca) {
                            sprintf(data, "%d %d %c", MOVE, hrac->IDhraca, hrac->smer);
                            gameCommunication(SEND, data);
                        }
                    }
                    hrac->smer = 0;

                    break;
                default:

                    break;
            }
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
    bomba->bombastrany.dole = 0;
    bomba->bombastrany.hore = 0;
    bomba->bombastrany.vpravo = 0;
    bomba->bombastrany.vlavo = 0;

    //zistenie kam moze vybuchnut bomba
    if (hra.mapa.velkost[bomba->y_Position + 1][bomba->x_Position] != Stena)bomba->bombastrany.dole = +1;
    if (hra.mapa.velkost[bomba->y_Position - 1][bomba->x_Position] != Stena)bomba->bombastrany.hore = -1;
    if (hra.mapa.velkost[bomba->y_Position][bomba->x_Position + 1] != Stena)bomba->bombastrany.vpravo = +1;
    if (hra.mapa.velkost[bomba->y_Position][bomba->x_Position - 1] != Stena)bomba->bombastrany.vlavo = -1;


    BOOM(bomba);
    //sleep(1);

    bomba->zijeBomba = 0;
    //vymazanieBombyZObrazovky(bomba, dole, hore, vlavo, vpravo);



    //hra.hraci[bomba.idHRACABOMBY].bomba[];
    //bomba->zijeBomba=0;
}

int trafilaHracaBomba(BOMBA *bomba, HRAC *hrac) {
    log_debug("som v akehohracatrafila bomba");
    if (((bomba->x_Position == hrac->x_Position) && (bomba->y_Position == hrac->y_Position)) ||
        ((bomba->x_Position == hrac->x_Position) &&
         (bomba->y_Position + bomba->bombastrany.hore == hrac->y_Position)) ||
        ((bomba->x_Position == hrac->x_Position) &&
         (bomba->y_Position + bomba->bombastrany.dole == hrac->y_Position)) ||
        ((bomba->x_Position + bomba->bombastrany.vlavo == (hrac->x_Position) &&
          bomba->y_Position == hrac->y_Position)) ||
        ((bomba->x_Position + bomba->bombastrany.vpravo == hrac->x_Position) &&
         (bomba->y_Position == hrac->y_Position))) {
        log_debug("som tu");
        return 1;
    }
    return 0;
}

void BOOM(BOMBA *bomba) {
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0;


    zmenavMape(bomba->y_Position, bomba->x_Position, Vybuch);
    zmenavMape(bomba->y_Position + bomba->bombastrany.dole, bomba->x_Position, Vybuch);
    zmenavMape(bomba->y_Position + bomba->bombastrany.hore, bomba->x_Position, Vybuch);
    zmenavMape(bomba->y_Position, bomba->x_Position + bomba->bombastrany.vpravo, Vybuch);
    zmenavMape(bomba->y_Position, bomba->x_Position + bomba->bombastrany.vlavo, Vybuch);


    if (trafilaHracaBomba(bomba, &hra.hraci[0])) {
        //log_debug("bomba trafila hraca1");
        hra.hraci[0].pocetZivotov--;
        hra.hraci[0].statistikahracavhre.pocetUmrti--;
        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a1 = 1;
        hra.hraci[0].frezze = 1;
    }

    if (trafilaHracaBomba(bomba, &hra.hraci[1])) {
        hra.hraci[1].pocetZivotov--;
        hra.hraci[1].statistikahracavhre.pocetUmrti--;
        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a2 = 2;
        hra.hraci[1].frezze = 1;
    }
    if (trafilaHracaBomba(bomba, &hra.hraci[2])) {
        hra.hraci[2].pocetZivotov--;
        hra.hraci[2].statistikahracavhre.pocetUmrti--;
        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a3 = 3;
        hra.hraci[2].frezze = 1;
    }
    if (trafilaHracaBomba(bomba, &hra.hraci[3])) {
        hra.hraci[3].pocetZivotov--;
        hra.hraci[3].statistikahracavhre.pocetUmrti--;
        hra.hraci[bomba->idHRACABOMBY].statistikahracavhre.pocetTrafenychHracov++;
        a4 = 4;
        hra.hraci[3].frezze = 1;
    }
    sleep(1);
    if (trafilaHracaBomba(bomba, &hra.hraci[0])) {
        //log_debug("bomba trafila hraca1");
        hra.hraci[0].frezze = 0;
    }

    if (trafilaHracaBomba(bomba, &hra.hraci[1])) {
        hra.hraci[1].frezze = 0;
    }
    if (trafilaHracaBomba(bomba, &hra.hraci[2])) {
        hra.hraci[2].frezze = 0;
    }
    if (trafilaHracaBomba(bomba, &hra.hraci[3])) {
        hra.hraci[3].frezze = 0;
    }

    vymazanieBombyZObrazovky(bomba);
//    zmenavMape(hra.hraci[0].y_Position, hra.hraci[0].x_Position, hra.hraci[0].znak);
    if (a1 == 1) {
        if (hra.hraci[0].mrtvy != 1) {
            zmenavMape(hra.hraci[0].y_Position, hra.hraci[0].x_Position, hra.hraci[0].znak);
            hra.hraci[0].frezze = 0;
        }
    }
    if (a2 == 2) {
        if (hra.hraci[1].mrtvy != 1) {
            zmenavMape(hra.hraci[1].y_Position, hra.hraci[1].x_Position, hra.hraci[1].znak);
            hra.hraci[1].frezze = 0;
        }
    }
    if (a3 == 3) {
        if (hra.hraci[2].mrtvy != 1) {
            zmenavMape(hra.hraci[2].y_Position, hra.hraci[2].x_Position, hra.hraci[2].znak);
            hra.hraci[2].frezze = 0;
        }
    }
    if (a4 == 4) {
        if (hra.hraci[3].mrtvy != 1) {
            zmenavMape(hra.hraci[3].y_Position, hra.hraci[3].x_Position, hra.hraci[3].znak);
            hra.hraci[3].frezze = 0;
        }
    }
}

void vymazanieBombyZObrazovky(BOMBA *bomba) {

    if (hra.mapa.velkost[bomba->y_Position][bomba->x_Position] == Vybuch) {
        zmenavMape(bomba->y_Position, bomba->x_Position, Prazdne);

    }
    if (hra.mapa.velkost[bomba->y_Position + bomba->bombastrany.dole][bomba->x_Position] == Vybuch) {
        zmenavMape(bomba->y_Position + bomba->bombastrany.dole, bomba->x_Position, Prazdne);

    }
    if (hra.mapa.velkost[bomba->y_Position + bomba->bombastrany.hore][bomba->x_Position] == Vybuch) {
        zmenavMape(bomba->y_Position + bomba->bombastrany.hore, bomba->x_Position, Prazdne);

    }
    if (hra.mapa.velkost[bomba->y_Position][bomba->x_Position + bomba->bombastrany.vpravo] == Vybuch) {
        zmenavMape(bomba->y_Position, bomba->x_Position + bomba->bombastrany.vpravo, Prazdne);

    }
    if (hra.mapa.velkost[bomba->y_Position][bomba->x_Position + bomba->bombastrany.vlavo] == Vybuch) {
        zmenavMape(bomba->y_Position, bomba->x_Position + bomba->bombastrany.vlavo, Prazdne);

    }
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

void mrtvyHrac(int pocetHracov) {
    for (int i = 0; i < pocetHracov; i++) {
        if ((hra.hraci[i].pocetZivotov == 0) && (hra.hraci[i].mrtvy == 0)) {
            hra.hraci[i].frezze = 1;
            zmenavMape(hra.hraci[i].y_Position, hra.hraci[i].x_Position, Prazdne);
            hra.hraci[i].x_Position = 0;
            hra.hraci[i].y_Position = 0;
            hra.hraci[i].mrtvy = 1;
        }

    }
}


void sendToServer() {


}

void acceptFromServer() {


}

void initGame(int pocetHracov, char *cesta, int mojeID) {
    //Inicializacia okna
    currentID = mojeID;
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

    log_debug("Krok1");
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
            hra.hraci[a].statistikahracavhre.pocetUmrti = 3;
            hra.hraci[a].mrtvy = 0;

//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, (char) hra.hraci[a].znak);
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
            hra.hraci[a].statistikahracavhre.pocetUmrti = 3;
            hra.hraci[a].mrtvy = 0;
//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, (char) hra.hraci[a].znak);
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
            hra.hraci[a].statistikahracavhre.pocetUmrti = 3;
            hra.hraci[a].mrtvy = 0;

//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, (char) hra.hraci[a].znak);
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
            hra.hraci[a].statistikahracavhre.pocetUmrti = 3;
            hra.hraci[a].mrtvy = 0;
//            log_debug("hrac cislo: %d ma ID:%d",a,hra.hraci[a].IDhraca);
            zmenavMape(hra.hraci[a].y_Position, hra.hraci[a].x_Position, (char) hra.hraci[a].znak);
        }
//        vykresliMapu();
    }
//    log_debug("HRAC 1 -- %c", hra.hraci[0].znak);
//    log_debug("HRAC 2 -- %c", hra.hraci[1].znak);

    pthread_t vlakno2;
    pthread_create(&vlakno2, 0, &delay, &hra.hraci[mojeID]);
    log_debug("SPUSTAM HRU");
    //todo ak hrac trafi bombu
    pthread_t vlak5;
    pthread_create(&vlak5, 0, &gameCom, NULL);

    while (1) {
//         for (int a = 0; a < pocetHracov; a++) {
//            log_debug("Hrac_ID: %d Ulozena bomba:%dx Umrtia:%dx Trafenie_Hraca: %dx",
//                      hra.hraci[a].statistikahracavhre.idHraca,
//                      hra.hraci[a].statistikahracavhre.pocetUlozenychBomb, hra.hraci[a].statistikahracavhre.pocetUmrti,
//                      hra.hraci[a].statistikahracavhre.pocetTrafenychHracov);
//         }
//        sleep(1);

        mrtvyHrac(pocetHracov);
        vykresliMapu();
        pohybHraca(&hra.hraci[currentID]);
        //vykresliMapu();

        printPlayersToScoreWindow();
//        if (socketReadyGame()) {
//            int pomS, pomT, pomId, pomAction;
//            scanf(dataFromRequest(), "%d %d %d %d", &pomS, &pomT, &pomId, &pomAction);
//
//            hra.hraci[pomId].smer = pomAction;
//            pohybHraca(&hra.hraci[pomId]);
////            switch (pomT) {
////                case MOVE:
////
////                    break;
////                default:
////                    break;
////            }
//        }
        //TODO ak ma hrac 0 zivotov furt ma poziciu kde umrel


    }
}

void *gameCom(void *a) {

    while (1) {
//        sleep(10);
//        hra.hraci[1].smer = 'b';
//        pohybHraca(&hra.hraci[1]);
        if (socketReadyGame() == true) {
            int pomS = 0, pomT = 0, pomId = 0;
            char pomAction;
            sscanf(dataFromBuffer(), "%d %d %d %c", &pomS, &pomT, &pomId, &pomAction);
            log_debug("pomS: %d, pomT: %d, pomID: %d, action: %c", pomS, pomT, pomId, pomAction);

            hra.hraci[pomId].smer = pomAction;
            pohybHraca(&hra.hraci[pomId]);
            log_debug("HRAC: %d , Smer: %c ", hra.hraci[pomId].IDhraca, hra.hraci[pomId].smer);


            if (pomId == 100)
                break;
            //            switch (pomT) {
//                case MOVE:
//
//                    break;
//                default:
//                    break;
//            }
            log_debug("Druhe vlakno  Preslo  %s", dataFromRequest());

        }
    }
//    int pomS, pomT, pomId, pomAction;
//    scanf(dataFromRequest(), "%d %d %d %d", &pomS, &pomT, &pomId, &pomAction);
//    hra.hraci[pomId].smer = pomAction;
//    pohybHraca(&hra.hraci[pomId]);
    pthread_exit(0);
}


