#ifndef BOMBERMAN_CLIENT_MENU_H
#define BOMBERMAN_CLIENT_MENU_H

#include <stdio.h>

//Struktura pre usera
struct Users{
    char name[10];
    char password[10];
}user;

//Struktura pre vytvorenie hry
struct Games{
    int cisloMapy;
    int pocetHracov;
}game;

void mainMenu();
void menuNewGame();
void menuFindServer();
void menuLeaderBoard();
void loginUser();

#endif
