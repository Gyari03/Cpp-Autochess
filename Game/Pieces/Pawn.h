#ifndef NHF_REFORMED_PAWN_H
#define NHF_REFORMED_PAWN_H
#include "../Piece.h"

class Pawn:public Piece {
public:
    Pawn(int x,int y);
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_PAWN_H