//
// Created by jurci on 9. 1. 2019.
//

#ifndef BOMBERMAN_CLIENT_GAMECONSTANTS_H
#define BOMBERMAN_CLIENT_GAMECONSTANTS_H


#define WALL '#'
#define EMPTY ' '
#define BARRIER '8'
#define BOMB_THREE 51
#define BOMB_TWO 50
#define BOMB_ONE 49
#define BOMB_BOOM '*'

#define NUMBER_THREE 51
#define NUMBER_ZERO 48

//#define PLAYER_ONE 'h'
//#define PLAYER_TWO 'j'
//#define PLAYER_THREE 'k'
//#define PLAYER_FOUR 'l'

enum color_pairs {
    PLAYER_ONE_PAIR = 1,
    PLAYER_TWO_PAIR = 2,
    PLAYER_THREE_PAIR = 3,
    PLAYER_FOUR_PAIR = 4,
    WALL_PAIR = 5,
    WALL_DESTROY_PAIR = 6,
    BOMB_PAIR = 7,
    EMPTY_PAIR = 8
};

enum gameEnum {
    IN_GAME,
    END,
    NON,
    SUCCESS,
    SEND
};


#endif //BOMBERMAN_CLIENT_GAMECONSTANTS_H
