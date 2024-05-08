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

void Piece::addMove(char to,int coord_x,int coord_y){
    Move* addedMove = new Move(this,x,y,to);
    this->piece_moves.addtoList(addedMove);
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

//Move függvények

bool checkAndAddMove(Game* game, Piece* from, int posX, int posY) { //diagonális, felfele lefele, balra jobbra jó lesz ez a függvény
    if (!(game->occupied(posX, posY))) {
        from->addMove('0', posX, posY);
    }
    else {
        Piece* other = game->searchfor(posX, posY);
        TeamColor colorOfOther = game->getColorOfPiece(other);
        TeamColor colorOfPiece = game->getColorOfPiece(from);

        if (colorOfOther != colorOfPiece) {
            char nameOfOther = other->getname();
            from->addMove(nameOfOther, posX, posY);
            return true; // Ha talált ilyen lépést, jelzi a kilépést
        }
        else{//Van másik bábu de mivel szövetséges nem üti le, viszont ki akarunk lépni
            return true;
        }
    }
    return false; // Ha nem talált ilyen lépést, folytatja a ciklust
}

void upwards(Piece* from,Game* game){
    int posX = from->getcoordX();
    int posY = from->getcoordY();
   // TeamColor colorOfPiece = game->getColorOfPiece(from);

    for(int i=posY;++i<=8;i++) {
        if(checkAndAddMove(game,from,posX,i)){break;}
    }
}

void downwards(Piece* from,Game* game){
    int posX = from->getcoordX();
    int posY = from->getcoordY();
  //  TeamColor colorOfPiece = game->getColorOfPiece(from);

    for(int i=posY;--i>=0;i--){
        if(checkAndAddMove(game,from,posX,i)){break;}
    }
}

void rightwards(Piece* from,Game* game){
    int posX = from->getcoordX();
    int posY = from->getcoordY();
//    TeamColor colorOfPiece = game->getColorOfPiece(from);

    for(int i=posX;++i<=8;i++){
        if(checkAndAddMove(game,from,i,posY)){break;}
    }
}

void leftwards(Piece* from,Game* game) {
    int posX = from->getcoordX();
    int posY = from->getcoordY();
  //  TeamColor colorOfPiece = game->getColorOfPiece(from);

    for(int i=posX;--i>=0;i--){
        if(checkAndAddMove(game,from,i,posY)){break;}
    }
}

void diagonalUpRight(Piece* from,Game* game){ //Y nő, X nő
    int posX = from->getcoordX();
    int posY = from->getcoordY();
   // TeamColor colorOfPiece = game->getColorOfPiece(from);
    posY++;posX++;
    while(posX<=8 && posY<=8){
        if(checkAndAddMove(game,from,posX,posY)){break;}
        posY++;posX++;
    }
}

void diagonalUpLeft(Piece* from, Game* game){ //Y nő, X csökken
    int posX = from->getcoordX();
    int posY = from->getcoordY();
   // TeamColor colorOfPiece = game->getColorOfPiece(from);
    posY++;posX--;
    while(posX>=1 && posY<=8){
        if(checkAndAddMove(game,from,posX,posY)){break;}
        posY++;posX--;
    }
}

void diagonalDownRight(Piece* from, Game* game){ //Y csökken, X nő
    int posX = from->getcoordX();
    int posY = from->getcoordY();
   // TeamColor colorOfPiece = game->getColorOfPiece(from);
    posY--;posX++;
    while(posX<=8 && posY>=1){
        if(checkAndAddMove(game,from,posX,posY)){break;}
        posY--;posX++;
    }
}

void diagonalDownLeft(Piece* from, Game* game){ //Y csökken, X csökken
    int posX = from->getcoordX();
    int posY = from->getcoordY();
  //  TeamColor colorOfPiece = game->getColorOfPiece(from);
    posY--;posX--;
    while(posX>=1 && posY>=1){
        if(checkAndAddMove(game,from,posX,posY)){break;}
        posY--;posX--;
    }
}

void pawnmove(Piece* from,Game* game){
    //alapvető adatok
    int posX = from->getcoordX();
    int posY = from->getcoordY();
    TeamColor colorOfPiece = game->getColorOfPiece(from);

    //eldönteni, hogy fehér vagy fekete és azáltal az irányát megadni a lépésnek
    if(colorOfPiece==White){posY++;}
    else{posY--;}

    //ELŐRE LÉPÉS
    if (!(game->occupied(posX, posY))) {
        from->addMove('0', posX, posY);
    }

    //Balra ütés beállítása
    posX--;

    //Balra ütés
    if(game->occupied(posX, posY)){
        Piece* other = game->searchfor(posX,posY);
        TeamColor colorOfOther = game->getColorOfPiece(other);
        if(colorOfOther!=colorOfPiece){
            char nameOfOther= other->getname();
            from->addMove(nameOfOther,posX,posY);
        }
    }

    //jobbra ütés beállítása
    posX+=2;

    //Jobbra ütés
    if(game->occupied(posX, posY)){
        Piece* other = game->searchfor(posX,posY);
        TeamColor colorOfOther = game->getColorOfPiece(other);
        if(colorOfOther!=colorOfPiece){
            char nameOfOther= other->getname();
            from->addMove(nameOfOther,posX,posY);
        }
    }
}

void horsemove(Piece* from, Game* game){
    //alapadatok
    int posX = from->getcoordX();
    int posY = from->getcoordY();

    //felfele
    if(posY+2<=8){//&& posX-2>=0 && posX+2<=8
        if(posX-2>=1){checkAndAddMove(game,from,posX-2,posY+2);}
        if(posX+2<=8){checkAndAddMove(game,from,posX+2,posY+2);}
    }

    //jobbra
    if(posX+2<=8){
        if(posY-2>=1){checkAndAddMove(game,from,posX+2,posY-2);}
        if(posY+2<=8){checkAndAddMove(game,from,posX+2,posY+2);}
    }

    //lefele
    if(posY-2<=8){
        if(posX-2>=1){checkAndAddMove(game,from,posX-2,posY-2);}
        if(posX+2<=8){checkAndAddMove(game,from,posX+2,posY-2);}
    }

    //balra
    if(posX-2<=8){
        if(posY-2>=1){checkAndAddMove(game,from,posX-2,posY-2);}
        if(posY+2<=8){checkAndAddMove(game,from,posX-2,posY+2);}
    }
}

void kingmove(Piece* from, Game* game){
    //alapadatok
    int posX = from->getcoordX();
    int posY = from->getcoordY();

    //felfele
    if(posY+1<=8){
        checkAndAddMove(game,from,posX,posY+1);
        if(posX+1<=8){checkAndAddMove(game,from,posX+1,posY+1);}
        if(posX-1>=1){checkAndAddMove(game,from,posX-1,posY+1);}
    }

    //jobbra
    if(posX+1<=8){
        checkAndAddMove(game,from,posX+1,posY);
        //a másik kettő már be van szedve a felfele és lefele részekből
    }

    //lefele
    if(posY-1>=1){
        checkAndAddMove(game,from,posX,posY-1);
        if(posX+1<=8){checkAndAddMove(game,from,posX+1,posY-1);}
        if(posX-1>=1){checkAndAddMove(game,from,posX-1,posY-1);}
    }

    //balra
    if(posX-1>=1){
        checkAndAddMove(game,from,posX-1,posY);
        //a másik kettő már be van szedve a felfele és lefele részekből
    }
}

void orthogonal(Piece* from, Game* game){
    upwards(from,game);
    downwards(from,game);
    rightwards(from,game);
    leftwards(from,game);
}

void diagonal(Piece* from, Game* game){
    diagonalDownLeft(from,game);
    diagonalDownRight(from,game);
    diagonalUpLeft(from,game);
    diagonalUpRight(from,game);
}