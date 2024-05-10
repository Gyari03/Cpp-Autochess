#include "Move.h"

#include "../Memtrace/memtrace.h"


Move::Move(Piece *originPiece, int coordX, int coordY, char destinationPieceName): from(originPiece), x(coordX), y(coordY), to(destinationPieceName){
    calculateWeight();
}

Move::~Move(){}

void Move::calculateWeight() {
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

bool Move::operator>(const Move& otherMove) const{
    if(this->weight > otherMove.weight){return true;}
    else{return false;}
}

Piece* Move::getPiece()const{
    return from;
}

int Move::getCoordX() const {
    return x;
}

int Move::getCoordY() const {
    return y;
}

int Move::getWeight() const {
    return weight;
}