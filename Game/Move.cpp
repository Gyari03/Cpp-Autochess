#include "Move.h"
//#include "Piece.h"


Move::Move(Piece *from, int x, int y, char to){
    calculateweight();
}

Move::~Move(){}

void Move::calculateweight() {
    switch(this->to){
        case '0': weight=0;break;
        case 'P': weight=1;break;
        case 'H': weight=3;break;
        case 'B': weight=4;break;
        case 'R': weight=5;break;
        case 'Q': weight=8;break;
        case 'K': weight=9;break;
        default: break;
    }
}

bool Move::operator>(const Move& other) const{
    if(this->weight>other.weight){return true;}
    else{return false;}
}