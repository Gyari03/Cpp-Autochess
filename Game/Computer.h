#ifndef NHF_REFORMED_COMPUTER_H
#define NHF_REFORMED_COMPUTER_H
#include "Team.h"

class Computer {
private:
    Team* white;
    Team* black;
public:
    Computer():white(nullptr),black(nullptr){}
    Computer(Team* white,Team* black):white(white),black(black){}
    void calculateMoves(TeamColor color){
        //FILLE FÜGGVÉNYEK CSAK HOGY LEFORDULJON //
        if(color==White){
            white->getArmy();
        }
        else
            black->getArmy();
    }

};


#endif //NHF_REFORMED_COMPUTER_H
