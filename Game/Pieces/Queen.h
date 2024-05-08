#ifndef NHF_REFORMED_QUEEN_H
#define NHF_REFORMED_QUEEN_H
#include "../Piece.h"

class Queen:public Piece {


public:
    Queen(int x,int y);
    void calculateMoves(Game* game) override;

};


#endif //NHF_REFORMED_QUEEN_H
