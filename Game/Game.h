#ifndef NHF_REFORMED_GAME_H
#define NHF_REFORMED_GAME_H
#include "Team.h"
#include "Army.h"



class Game {
private:
    Team* team[2];//Team pointerekből 2-őt tárol [0]:fehér [1]:fekete //A Gamekonstruktorból hozódik létre a 2 team a Team konstruktorokból(Army*,Szin)
    Army white;
    Army black;

public:
    Game(Army white,Army black);//rendes létrehozás
    void setupBoard();

};


#endif //NHF_REFORMED_GAME_H
