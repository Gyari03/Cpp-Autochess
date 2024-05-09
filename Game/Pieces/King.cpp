#include "King.h"
#include "../../Memtrace/memtrace.h"


King::King(int x,int y):Piece('K',x,y){}

void King::calculateMoves(Game* game){
    kingmove(this,game);
}
