#ifndef NHF_REFORMED_KING_H
#define NHF_REFORMED_KING_H
#include "../Piece.h"

class King:public Piece {
public:
    King(int x,int y);
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_KING_H