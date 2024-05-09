#include "Queen.h"
#include "../../Memtrace/memtrace.h"


Queen::Queen(int x,int y):Piece('Q',x,y){}
void Queen::calculateMoves(Game* game){
    diagonal(this,game);
    orthogonal(this,game);
}