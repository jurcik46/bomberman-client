////
//// Created by sterb on 9. 1. 2019.
////
//
//#ifndef BOMBERMAN_CLIENT_HRAC_H
//#define BOMBERMAN_CLIENT_HRAC_H
//
//#include <stdio.h>
//#include <curses.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include "mapa.h"
//
//#define POCET_HRACOV 4
//#define MAX_POCETBOMB 3
//
//enum Hraci{
//    PLAYER_ONE = 49,
//    PLAYER_TWO = 50,
//    PLAYER_THREE = 51,
//    PLAYER_FOUR = 52
//};
//
//enum Prekazky{
//
//    Vybuch = 89,
//    Stena = 35,
//    Prazdne = 32
//};
//
//typedef struct mapa{
//    char** velkost;
//    int x;
//    int y;
//    pthread_mutex_t  *mutex;
//}MAPA;
//
///**
// * Struktura pre bombu
// */
//typedef struct bomba{
//    int x_Position;
//    int y_Position;
//    int idHRACABOMBY;
//    char znak;
//}BOMBA;
//
//typedef struct hra{
//    MAPA  mapa;
//    int pocetHracov;
//    HRAC hraci[POCET_HRACOV];
//}HRA;
//
///**
// * Struktura pre hraca
// */
//typedef struct hrac{
//    int x_Position;
//    int y_Position;
//    int znak;
//    BOMBA bomba[3];
//    int smer;
//    int pocetZivotov;
//    int IDhraca;
//    int cislo_bomby;
//    pthread_mutex_t  *mutex;
//}HRAC;
//
//HRA hra;
//
//void initGame(int pocetHracov,char *cesta,int mojeID);
//
//void *delay(void *hrac);
//
//void *delay2(void *hrac);
//
//void pohybHraca(HRAC * hrac);
//
//char** createM(int m, int n);
//
//void deletM(int m, char ***mat);
//
//
///**
// * Funkcie pre bomby
// * @param hra
// * @return
// */
//void *odpocetBomby(void * hra);
//
//void BOOM(BOMBA * bomba,int dole,int hore,int vlavo,int vpravo);
//
//void vymazanieBombyZObrazovky(BOMBA * bomba,int dole,int hore,int vlavo,int vpravo);
//
//void vytvorBombu(HRAC * hrac,int cisloBomby);
//
//void vytvorVlaknoPreBombu(void *(*startovaciaFunkcia)(void *),BOMBA * bomba);
//
//void vybuchBomby(BOMBA bomba);
//
//#endif //BOMBERMAN_CLIENT_HRAC_H

//
// Created by Phixell on 6. 1. 2019.
//

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
 */
typedef struct bomba{
    int x_Position;
    int y_Position;
    int idHRACABOMBY;
    char znak;
    int zijeBomba;
    int cas;
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

void initGame(int pocetHracov,char *cesta,int mojeID);

void *delay(void *hrac);

void pohybHraca(HRAC * hrac);

/**
 * FUnkcie pre bomby
 * @param hra
 * @return
 */

void *odpocetBomby(void * hra);

void BOOM(BOMBA * bomba,int dole,int hore,int vlavo,int vpravo);

void vymazanieBombyZObrazovky(BOMBA * bomba,int dole,int hore,int vlavo,int vpravo);

void vytvorBombu(HRAC * hrac,int cisloBomby);

void vytvorVlaknoPreBombu(void *(*startovaciaFunkcia)(void *),BOMBA * bomba);

void vybuchBomby(BOMBA * bomba);

#endif //BOMBERMAN_CLIENT_HRA_H
