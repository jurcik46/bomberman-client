#ifndef BOMBERMAN_CLIENT_HRA_H
#define BOMBERMAN_CLIENT_HRA_H

#include <sys/param.h>
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "../logging/log.h"
#include "mapa.h"
#define POCET_HRACOV 4
#define MAX_POCETBOMB 3


enum Hraci{
    PLAYER_ONE = 'h',
    PLAYER_TWO = 'j',
    PLAYER_THREE = 'k',
    PLAYER_FOUR = 'l'
};

enum Prekazky{
    Vybuch = 42,
    Stena = 35,
    Prazdne = 32
};

//enum Mapa{
//    mapa1= ../Mapa/1.txt,
//    mapa2= ../Mapa/2.txt,
//    mapa3= ../Mapa/3.txt
//
//};

typedef  struct statistikaHracaVHre{
    int pocetUmrti;
    int pocetUlozenychBomb;
    int pocetTrafenychHracov;
    char meno[30];
    int idHraca;
}STATISTIKAHRACAVHRE ;

typedef struct mapa{
    char** velkost;
    int x;
    int y;
    pthread_mutex_t  *mutex;
}MAPA;

/**
 * Struktura pre bombu
 *
 * */
typedef struct vybuchBombyStrany{
    int hore;
    int dole;
    int vlavo;
    int vpravo;

}VYBUCHBOMBYSTRANY;

typedef struct bomba{
    int x_Position;
    int y_Position;
    int idHRACABOMBY;
    char znak;
    int zijeBomba;
    int cas;
    VYBUCHBOMBYSTRANY bombastrany;
}BOMBA;

/**
 * Struktura pre hraca
 */
typedef struct hrac{
    int x_Position;
    int y_Position;
    int znak;
    BOMBA bomba[MAX_POCETBOMB];
    int smer;
    int pocetZivotov;
    int IDhraca;
    int cislo_bomby;
    STATISTIKAHRACAVHRE statistikahracavhre;
    pthread_mutex_t  *mutex;
}HRAC;

typedef struct hra{
    MAPA  mapa;
    int pocetHracov;
    HRAC hraci[POCET_HRACOV];
}HRA;

HRA hra;

char** createM(int m, int n);

void printPlayersToScoreWindow();

void initGame(int pocetHracov,char *cesta,int mojeID);

void *delay(void *hrac);

void pohybHraca(HRAC * hrac);

/**
 * FUnkcie pre bomby
 * @param hra
 * @return
 */

int trafilSomVBombuHracaID(HRAC *hrac);

void *odpocetBomby(void * hra);

void BOOM(BOMBA * bomba);

void vymazanieBombyZObrazovky(BOMBA * bomba);

void vytvorBombu(HRAC * hrac,int cisloBomby);

void vytvorVlaknoPreBombu(void *(*startovaciaFunkcia)(void *),BOMBA * bomba);

int trafilaHracaBomba(BOMBA *bomba, HRAC * HRAC);

void vybuchBomby(BOMBA * bomba);

#endif //BOMBERMAN_CLIENT_HRA_H
