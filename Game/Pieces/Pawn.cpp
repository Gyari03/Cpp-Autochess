#include "Pawn.h"
#include "../../Memtrace/memtrace.h"


Pawn::Pawn(int x,int y):Piece('P',x,y){}
void Pawn::calculateMoves(Game* game){
    pawnMove(this, game);
}