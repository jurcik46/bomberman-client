//
// Created by Jurco on 22. 11. 2018.
//

#ifndef BOMBERMAN_CLIENT_CONSTANTS_H
#define BOMBERMAN_CLIENT_CONSTANTS_H

enum result_code {
    ZERO = 0, OKEJ = 200, CREATED = 201, UNAUTHORIZED = 401, INTERNAL_SERVER_ERROR = 500
};

enum communication_type {
    LOGIN,
};

enum menu_choices {
    EXIT = 15, //preto 15 lebo taka moznost sa nepouziva nikde v menu
    MENU_NEW_GAME = 0,
    MENU_FIND_SERVER = 1,
    MENU_LEADER_BOARD = 2,
    MENU_EXIT = 3,
    START_GAME = 0,
    MAIN_MENU = 1,
    ENTER = 10
};

#endif //BOMBERMAN_CLIENT_CONSTANTS_H
