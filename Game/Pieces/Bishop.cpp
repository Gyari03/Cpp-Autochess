#include "Bishop.h"
#include "../../Memtrace/memtrace.h"

Bishop::Bishop(int x,int y):Piece('B',x,y){}

void Bishop::calculateMoves(Game* game) {
    diagonal(this,game);
}