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
#include <pthread.h>
#include <assert.h>

#include "../logging/log.h"
#include "../communication.h"
#include "../constants.h"

#define WIN_HEIGHT 20
#define WIN_WIDTH 90
#define LOBBY_WIN_SIZE 6
#define NAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define GAME_NAME_LENGTH 20
#define RESET_CHOICE -1
#define MAX_GAMES 20

//Struktura pre usera
typedef struct user {
    int id;
    char name[NAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

//Struktura pre vytvorenie hry
typedef struct game {
    int gameId;
    char nazovHry[GAME_NAME_LENGTH];
    int cisloMapy;
    int pocetHracov;
    int maxPocetHracov;
    _Bool admin;
    User users[4];
} Game;

//Struktura pre druhe vlakno na obsluzenie vstupu od uztivatela
typedef struct choice {
    pthread_mutex_t mutex;
    int choice;
    WINDOW *lobby_Win;
    _Bool result;
} CHOICE;

WINDOW *my_window;
int startX, startY;
int choice;
bool success;

Game game;

Game emptyGame;

User user;

void initNcurses();

void refreshWindow(WINDOW* window);

void menu();

void loginUser(WINDOW *my_window);

int mainMenu(WINDOW *my_window);

bool menuNewGame(WINDOW *my_window);

int menuFindServer(WINDOW *my_window);

void menuLeaderBoard(WINDOW *my_window);

int menuLobby(WINDOW *my_window, int startY, int startX);

int lobbyChoice(CHOICE *param, pthread_t *thread);


#endif
