#ifndef BOMBERMAN_CLIENT_MENU_H
#define BOMBERMAN_CLIENT_MENU_H

#include <stdio.h>
#include <curses.h>

#define WIN_HEIGHT 20
#define WIN_WIDTH 90
#define LOBBY_WIN_SIZE 6

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

void loginUser(WINDOW *my_window);
int mainMenu(WINDOW *my_window);
bool menuNewGame(WINDOW *my_window);
void menuFindServer(WINDOW *my_window);
void menuLeaderBoard(WINDOW *my_window);
int menuLobby(WINDOW *my_window, int startY, int startX);

#endif
