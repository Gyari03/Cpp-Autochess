#include "Piece.h"
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include "Pieces/Horse.h"
#include "Pieces/Pawn.h"
#include "Game.h"

#include <cctype>


#include "../Memtrace/memtrace.h"

Piece::Piece(char name,int x,int y):y(y),x(x),name(name) {}



int Piece::getcoordY() const {
    return y;
}

int Piece::getcoordX() const {
    return x;
}

char Piece::getname() const {
    return name;
}

void Piece::setcoordY(int j) {
    this->y=j;
}

void Piece::setcoordX(int i) {
    this->x=i;
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
    //hiba kezelés kiindexelés esetén:

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

void Piece::addMove(char to,int coord_x,int coord_y){
    Move* addedMove = new Move(this,x,y,to);
    this->piece_moves.addtoList(addedMove);
}


//Move függvények

void upwards(Piece* from,Game* game){
    int posX = from->getcoordX();
    int posY = from->getcoordY();
    TeamColor colorOfPiece = game->getColorOfPiece(from);

    for(int i=posY;++i<=8;i++){
        if(!(game->occupied(posX,i))){
            from->addMove('0',posX,i);
        }
        else{//ha a mező occupied
            Piece* other = game->searchfor(posX,i); //akivel ütközik
            TeamColor colorOfOther = game->getColorOfPiece(other);
            if(colorOfOther==colorOfPiece){return;}
            else{
                char nameOfOther =other->getname();
                from->addMove(nameOfOther,posX,i);
            }//na nem ugyanaz a csapat leütheti a másikat
        }
    }
}












