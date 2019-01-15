//
// Created by Jurco on 22. 11. 2018.
//

#ifndef BOMBERMAN_CLIENT_CONSTANTS_H
#define BOMBERMAN_CLIENT_CONSTANTS_H

enum result_code {
    ZERO = 0,
    OKEJ = 200,
    CREATED = 201,
    DONE = 204,
    UNAUTHORIZED = 401,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    SERVICE_UNAVAILABLE = 503
};

enum communication_type {
    LOGIN,
    CREATE_GAME,
    REGISTRATION,
    GET_LOBBY_PLAYER,
    FIND_SERVERS,
    JOIN_LOBBY,
    LEAVE_LOBBY,
    MAP_DOWNLOAD,
    START,
};

enum menu_choices {
    //TODO pomenit hodnoty aby neboli rovnake a otestovat menu pripadne doladit
            EXIT = 15, //preto 15 lebo taka moznost sa nepouziva nikde v menu
    MENU_NEW_GAME = 0,
    MENU_FIND_SERVER = 1,
    MENU_LEADER_BOARD = 2,
    MENU_EXIT = 3,
    START_GAME = 0,
    MAIN_MENU = 1,
    ENTER = 10,
    ESC = 27,
    DEFAULT = 1000,
    JOIN = 1001


};

#endif //BOMBERMAN_CLIENT_CONSTANTS_H
