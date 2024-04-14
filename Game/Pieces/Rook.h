#ifndef NHF_REFORMED_ROOK_H
#define NHF_REFORMED_ROOK_H
#include "../Piece.h"

class Rook:public Piece {



public:
    Rook(int x,int y):Piece('R',x,y){}
    void calculateMoves() override{}

};


#endif //NHF_REFORMED_ROOK_H
