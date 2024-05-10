#ifndef NHF_REFORMED_COMPUTER_H
#define NHF_REFORMED_COMPUTER_H
#include "Team.h"

class Computer {
public:
    Computer();
    void calculateMoves(Game* game);
    Move* decideMove(Game* game);
};
#endif //NHF_REFORMED_COMPUTER_H