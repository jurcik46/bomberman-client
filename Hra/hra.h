//
// Created by sterb on 9. 1. 2019.
//

#ifndef BOMBERMAN_CLIENT_HRAC_H
#define BOMBERMAN_CLIENT_HRAC_H

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mapa.h"

#define POCET_HRACOV 4

typedef struct mapa{
    char** velkost;
    int x;
    int y;
    pthread_mutex_t  *mutex;
}MAPA;

typedef struct hra{
    MAPA  mapa;
    int pocetHracov;
    //HRAC hraci[POCET_HRACOV];
}HRA;

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
//
//
//    pthread_mutex_t  *mutex;
//}HRAC;

HRA hra;

char** createM(int m, int n);

void deletM(int m, char ***mat);

#endif //BOMBERMAN_CLIENT_HRAC_H
