#include "Piece.h"
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include "Pieces/Horse.h"
#include "Pieces/Pawn.h"

#include <cctype>

Piece::Piece(char name,int x,int y):name(name),x(x),y(y) {}



int Piece::getcoordY() const {
    return y;
}

int Piece::getcoordX() const {
    return x;
}

char Piece::getname() const {
    return name;
}

void Piece::setcoordY(int y) {
    this->y=y;
}

void Piece::setcoordX(int x) {
    this->x=x;
}

bool Piece::operator==(const Piece &other)const{
    if(this->y==other.y && this->x==other.x)
        return true;
    else
        return false;
}

void Piece::tolowercase() {
    name = (char)tolower(name);
}

Piece* createPiece(char name,int x,int y){
    name = (char) toupper(name);
    Piece *piece=nullptr;
    switch(name){
        case 'K':piece = new King(x,y);break;
        case 'Q':piece = new Queen(x,y);break;
        case 'R':piece = new Rook(x,y);break;
        case 'B':piece = new Bishop(x,y);break;
        case 'H':piece = new Horse(x,y);break;
        case 'P':piece = new Pawn(x,y);break;
        default: break;
    }
    return piece;
}