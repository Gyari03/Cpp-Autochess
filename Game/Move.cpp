#include "Move.h"

#include "../Memtrace/memtrace.h"


Move::Move(Piece *originPiece, int coordX, int coordY, char destinationPieceName): originPiece(originPiece), destinationX(coordX), destinationY(coordY), destinationPieceName(destinationPieceName){
    calculateWeight();
}

Move::~Move(){}

void Move::calculateWeight() {
    switch(this->destinationPieceName){
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
    return originPiece;
}

int Move::getCoordX() const {
    return destinationX;
}

int Move::getCoordY() const {
    return destinationY;
}

int Move::getWeight() const {
    return weight;
}