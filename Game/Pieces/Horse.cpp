#include "Horse.h"
#include "../../Memtrace/memtrace.h"

Horse::Horse(int x,int y):Piece('H',x,y){}

void Horse::calculateMoves(Game* game) {
    horseMove(this, game);
}