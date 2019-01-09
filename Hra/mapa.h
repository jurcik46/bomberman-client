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

WINDOW *mapWindow;

void zistiVelkostMapy(char *menoMapy);

void nacitajMapu(char *menoMapy);

void zmenavMape(int py,int px,int c);

void vykresliMapu();

void initMap(int cisloMapy);

#endif //BOMBERMAN_CLIENT_MAPA_H
