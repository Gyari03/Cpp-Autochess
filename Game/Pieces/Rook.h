#ifndef NHF_REFORMED_ROOK_H
#define NHF_REFORMED_ROOK_H
#include "../Piece.h"

class Rook:public Piece {
public:
    Rook(int x,int y);
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_ROOK_H