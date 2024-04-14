#ifndef NHF_REFORMED_KING_H
#define NHF_REFORMED_KING_H
#include "../Piece.h"


class King:public Piece {



public:
    King(int x,int y):Piece('K',x,y){}
    void calculateMoves() override{}

};


#endif //NHF_REFORMED_KING_H
