#ifndef BOMBERMAN_CLIENT_MENU_H
#define BOMBERMAN_CLIENT_MENU_H

#include <stdio.h>
#include <curses.h>

//Struktura pre usera
struct Users{
    char name[10];
    char password[10];
}user;

//Struktura pre vytvorenie hry
struct Games{
    char nazovHry[20];
    int cisloMapy;
    int pocetHracov;
}game;

void mainMenu(WINDOW *my_window);
void menuNewGame(WINDOW *my_window);
void menuFindServer(WINDOW *my_window);
void menuLeaderBoard(WINDOW *my_window);
void loginUser(WINDOW *my_window);

#endif
