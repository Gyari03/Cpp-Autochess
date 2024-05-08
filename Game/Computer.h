#ifndef NHF_REFORMED_COMPUTER_H
#define NHF_REFORMED_COMPUTER_H
#include "Team.h"

class Computer {
private:
    Team* white;
    Team* black;
public:
    Computer();
    Computer(Team* white,Team* black);
    void calculateMoves(Game* game); //true=feher false =fekete
    Move* decideMove(Game* game);
};


#endif //NHF_REFORMED_COMPUTER_H
