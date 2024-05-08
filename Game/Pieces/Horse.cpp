#include "Horse.h"

Horse::Horse(int x,int y):Piece('H',x,y){}

void Horse::calculateMoves(Game* game) {
    horsemove(this,game);
}