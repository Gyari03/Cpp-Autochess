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

Piece::Piece(char name, int coordX, int coordY): y(coordY), x(coordX), name(name) {}

int Piece::getCoordY() const {
    return y;
}

int Piece::getCoordX() const {
    return x;
}

char Piece::getName() const {
    return name;
}

List<Move>& Piece::getMoves()  {
    return piece_moves;
}

void Piece::setCoordY(int newY) {
    this->y=newY;
}

void Piece::setCoordX(int newX) {
    this->x=newX;
}

bool Piece::operator==(const Piece &otherPiece)const{
    if(this->y == otherPiece.y && this->x == otherPiece.x)
        return true;
    else
        return false;
}

void Piece::toLowercase() {
    name = (char)tolower(name);
}

void Piece::addMove(char destinationPieceName, int coordX, int coordY){
    Move* addedMove = new Move(this, coordX, coordY, destinationPieceName);
    this->piece_moves.addtoList(addedMove);
}

Piece* Piece::createPiece(char name,int x,int y){
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

//Move függvények

bool Piece::checkAndAddMove(Game* game, Piece* originPiece, int posX, int posY) { //diagonális, felfele lefele, balra jobbra jó lesz ez a függvény
    if (!(game->occupied(posX, posY))) {
        originPiece->addMove('0', posX, posY);
    }
    else {
        Piece* other = game->searchFor(posX, posY);
        TeamColor colorOfOther = game->getColorOfPiece(other);
        TeamColor colorOfPiece = game->getColorOfPiece(originPiece);

        if (colorOfOther != colorOfPiece) {
            char nameOfOther = other->getName();
            originPiece->addMove(nameOfOther, posX, posY);
            return true; // Ha talált ilyen lépést, jelzi a kilépést
        }
        else{//Van másik bábu de mivel szövetséges nem üti le, viszont ki akarunk lépni
            return true;
        }
    }
    return false; // Ha nem talált ilyen lépést, folytatja a ciklust
}

void Piece::upwards(Piece* originPiece, Game* game){
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
    int i = posY;i++;
    while(i<=8){
        if(checkAndAddMove(game, originPiece, posX, i)){break;}
        i++;
    }
}

void Piece::downwards(Piece* originPiece, Game* game){
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
    int i = posY;i--;
    while(i>=1){
        if(checkAndAddMove(game, originPiece, posX, i)){break;}
        i--;
    }
}

void Piece::rightwards(Piece* originPiece, Game* game){
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
    int i = posX;i++;
    while(i<=8){
        if(checkAndAddMove(game, originPiece, i, posY)){break;}
        i++;
    }
}

void Piece::leftwards(Piece* originPiece, Game* game) {
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
    int i = posX;i--;
    while(i>=1){
        if(checkAndAddMove(game, originPiece, i, posY)){break;}
        i--;
    }
}

void Piece::diagonalUpRight(Piece* originPiece, Game* game){ //Y nő, X nő
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
   // TeamColor colorOfPiece = game->getColorOfPiece(originPiece);
    posY++;posX++;
    while(posX<=8 && posY<=8){
        if(checkAndAddMove(game, originPiece, posX, posY)){break;}
        posY++;posX++;
    }
}

void Piece::diagonalUpLeft(Piece* originPiece, Game* game){ //Y nő, X csökken
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
   // TeamColor colorOfPiece = game->getColorOfPiece(originPiece);
    posY++;posX--;
    while(posX>=1 && posY<=8){
        if(checkAndAddMove(game, originPiece, posX, posY)){break;}
        posY++;posX--;
    }
}

void Piece::diagonalDownRight(Piece* originPiece, Game* game){ //Y csökken, X nő
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
   // TeamColor colorOfPiece = game->getColorOfPiece(originPiece);
    posY--;posX++;
    while(posX<=8 && posY>=1){
        if(checkAndAddMove(game, originPiece, posX, posY)){break;}
        posY--;posX++;
    }
}

void Piece::diagonalDownLeft(Piece* originPiece, Game* game){ //Y csökken, X csökken
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
  //  TeamColor colorOfPiece = game->getColorOfPiece(originPiece);
    posY--;posX--;
    while(posX>=1 && posY>=1){
        if(checkAndAddMove(game, originPiece, posX, posY)){break;}
        posY--;posX--;
    }
}

void Piece::pawnMove(Piece* originPiece, Game* game){
    //alapvető adatok
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();
    TeamColor colorOfPiece = game->getColorOfPiece(originPiece);

    //eldönteni, hogy fehér vagy fekete és azáltal az irányát megadni a lépésnek
    if(colorOfPiece==White){posY++;}
    else{posY--;}

    //ELŐRE LÉPÉS
    bool notOutOfBoundsY = (posY>=1)&&(posY<=8); //csak Y-ra kell nézni
    if ( (!(game->occupied(posX, posY))) && notOutOfBoundsY ) {
        originPiece->addMove('0', posX, posY);
    }

    //Balra ütés beállítása
    posX--;

    //Balra ütés
    if(game->occupied(posX, posY)){
        Piece* other = game->searchFor(posX, posY);
        TeamColor colorOfOther = game->getColorOfPiece(other);
        if(colorOfOther!=colorOfPiece){
            char nameOfOther= other->getName();
            originPiece->addMove(nameOfOther, posX, posY);
        }
    }

    //jobbra ütés beállítása
    posX+=2;

    //Jobbra ütés
    if(game->occupied(posX, posY)){
        Piece* other = game->searchFor(posX, posY);
        TeamColor colorOfOther = game->getColorOfPiece(other);
        if(colorOfOther!=colorOfPiece){
            char nameOfOther= other->getName();
            originPiece->addMove(nameOfOther, posX, posY);
        }
    }
}

void Piece::horseMove(Piece* originPiece, Game* game){
    //alapadatok
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();

    //felfele
    if(posY+2<=8){//&& posX-2>=0 && posX+2<=8
        if(posX-1>=1){checkAndAddMove(game, originPiece, posX - 1, posY + 2);}
        if(posX+1<=8){checkAndAddMove(game, originPiece, posX + 1, posY + 2);}
    }

    //jobbra
    if(posX+2<=8){
        if(posY-1>=1){checkAndAddMove(game, originPiece, posX + 2, posY - 1);}
        if(posY+1<=8){checkAndAddMove(game, originPiece, posX + 2, posY + 1);}
    }

    //lefele
    if(posY-2>=1){ //    if(posY-2<=8){
        if(posX-1>=1){checkAndAddMove(game, originPiece, posX - 1, posY - 2);}
        if(posX+1<=8){checkAndAddMove(game, originPiece, posX + 1, posY - 2);}
    }

    //balra
    if(posX-2>=1){ //    if(posX-2<=8){
        if(posY-1>=1){checkAndAddMove(game, originPiece, posX - 2, posY - 1);}
        if(posY+1<=8){checkAndAddMove(game, originPiece, posX - 2, posY + 1);}
    }
}

void Piece::kingMove(Piece* originPiece, Game* game){
    //alapadatok
    int posX = originPiece->getCoordX();
    int posY = originPiece->getCoordY();

    //felfele
    if(posY+1<=8){
        checkAndAddMove(game, originPiece, posX, posY + 1);
        if(posX+1<=8){checkAndAddMove(game, originPiece, posX + 1, posY + 1);}
        if(posX-1>=1){checkAndAddMove(game, originPiece, posX - 1, posY + 1);}
    }

    //jobbra
    if(posX+1<=8){
        checkAndAddMove(game, originPiece, posX + 1, posY);
        //a másik kettő már be van szedve a felfele és lefele részekből
    }

    //lefele
    if(posY-1>=1){
        checkAndAddMove(game, originPiece, posX, posY - 1);
        if(posX+1<=8){checkAndAddMove(game, originPiece, posX + 1, posY - 1);}
        if(posX-1>=1){checkAndAddMove(game, originPiece, posX - 1, posY - 1);}
    }

    //balra
    if(posX-1>=1){
        checkAndAddMove(game, originPiece, posX - 1, posY);
        //a másik kettő már be van szedve a felfele és lefele részekből
    }
}

void Piece::orthogonal(Piece* originPiece, Game* game){
    upwards(originPiece, game);
    downwards(originPiece, game);
    rightwards(originPiece, game);
    leftwards(originPiece, game);
}

void Piece::diagonal(Piece* originPiece, Game* game){
    diagonalDownLeft(originPiece, game);
    diagonalDownRight(originPiece, game);
    diagonalUpLeft(originPiece, game);
    diagonalUpRight(originPiece, game);
}