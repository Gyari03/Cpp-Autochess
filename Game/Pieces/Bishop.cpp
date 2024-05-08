#include "Bishop.h"

Bishop::Bishop(int x,int y):Piece('B',x,y){}

void Bishop::calculateMoves(Game* game) {
    orthogonal(this,game);
}