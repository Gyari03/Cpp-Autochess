#ifndef NHF_REFORMED_HORSE_H
#define NHF_REFORMED_HORSE_H
#include "../Piece.h"

class Horse:public Piece {
public:
    Horse(int x,int y);
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_HORSE_H