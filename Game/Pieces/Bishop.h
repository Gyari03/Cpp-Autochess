#ifndef NHF_REFORMED_BISHOP_H
#define NHF_REFORMED_BISHOP_H
#include "../Piece.h"

class Bishop:public Piece{
public:
    Bishop(int x,int y):Piece('B',x,y){}
    void calculateMoves() override{}
};


#endif //NHF_REFORMED_BISHOP_H
