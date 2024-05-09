#include "Move.h"

#include "../Memtrace/memtrace.h"


Move::Move(Piece *from, int x, int y, char to):from(from),x(x),y(y),to(to){
    calculateweight();
}

Move::~Move(){}

void Move::calculateweight() {
    switch(this->to){
        case '0': weight=0;break;
        case 'p':
        case 'P': weight=1;break;
        case 'h':
        case 'H': weight=3;break;
        case 'b':
        case 'B': weight=4;break;
        case 'r':
        case 'R': weight=5;break;
        case 'q':
        case 'Q': weight=8;break;
        case 'k':
        case 'K': weight=9;break;
        default: break;
    }
}

bool Move::operator>(const Move& other) const{
    if(this->weight>other.weight){return true;}
    else{return false;}
}

Piece* Move::getPiece()const{
    return from;
}

int Move::getX() const {
    return x;
}

int Move::getY() const {
    return y;
}

int Move::getWeight() const {
    return weight;
}