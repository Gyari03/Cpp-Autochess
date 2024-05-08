#include "Pawn.h"

Pawn::Pawn(int x,int y):Piece('P',x,y){}
void Pawn::calculateMoves(Game* game){
    pawnmove(this,game);
}