#ifndef NHF_REFORMED_BISHOP_H
#define NHF_REFORMED_BISHOP_H
#include "../Piece.h"

class Bishop:public Piece{
public:
    Bishop(int x,int y);
    void calculateMoves(Game* game) override;
};


#endif //NHF_REFORMED_BISHOP_H
