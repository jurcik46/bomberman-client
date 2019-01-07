#ifndef BOMBERMAN_CLIENT_MENU_H
#define BOMBERMAN_CLIENT_MENU_H

#include <stdio.h>
#include <curses.h>
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../logging/log.h"
#include "../communication.h"
#include "../constants.h"

#define WIN_HEIGHT 20
#define WIN_WIDTH 90
#define LOBBY_WIN_SIZE 6
#define NAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define GAME_NAME_LENGTH 20

//Struktura pre usera
struct Users {
    _Bool admin;
    char name[NAME_LENGTH];
    char password[PASSWORD_LENGTH];
} user;

//Struktura pre vytvorenie hry
struct Games {
    char nazovHry[GAME_NAME_LENGTH];
    int cisloMapy;
    int pocetHracov;
    struct Users users[4];
} game;

WINDOW *my_window;
int startX, startY;
int choice;
bool success;

void initNcurses();

void loginUser(WINDOW *my_window);

int mainMenu(WINDOW *my_window);

bool menuNewGame(WINDOW *my_window);

void menuFindServer(WINDOW *my_window);

void menuLeaderBoard(WINDOW *my_window);

int menuLobby(WINDOW *my_window, int startY, int startX);

#endif
