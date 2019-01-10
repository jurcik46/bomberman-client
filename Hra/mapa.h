//
// Created by sterb on 9. 1. 2019.
//

#ifndef BOMBERMAN_CLIENT_MAPA_H
#define BOMBERMAN_CLIENT_MAPA_H

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hra.h"
#include "gameConstants.h"

#define SCORE_WIN_Y 30
#define SCORE_WIN_X 50

WINDOW *mapWindow;

WINDOW *scoreWindow;

void zistiVelkostMapy(char *menoMapy);

void nacitajMapu(char *menoMapy);

void zmenavMape(int py,int px, char c);

void vykresliMapu();

void initMap(int cisloMapy);

void initColor();

void printElement(int y, int x, char pom);

void printPlayer(int y, int x, char znak);

#endif //BOMBERMAN_CLIENT_MAPA_H
