#include "Rook.h"

Rook::Rook(int x,int y):Piece('R',x,y){}
void Rook::calculateMoves(Game* game){
    orthogonal(this,game);
}