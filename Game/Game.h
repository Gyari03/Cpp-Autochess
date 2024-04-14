#ifndef NHF_REFORMED_GAME_H
#define NHF_REFORMED_GAME_H
#include "Team.h"
#include "Army.h"



class Game {
private:
    Team team[2];//team[0]:white team[1]:black
    Army white;
    Army black;

public:
    Game(Army white,Army black);//rendes létrehozás
    void setupBoard(Army white,Army black); //assuming its 8x8, for bigger boards other setups must be made

};


#endif //NHF_REFORMED_GAME_H
