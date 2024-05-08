#ifndef NHF_REFORMED_PIECE_H
#define NHF_REFORMED_PIECE_H
#include "../List/List.hpp"
#include "Move.h"


class Game;

class Piece { //absztrakt osztály
private:
    int y,x;
    char name;//egy karakter lehet csak, alosztályok konstruktoránál kap értéket
protected:
    List<Move> piece_moves;

public:
    Piece(char name,int x=0,int y=0);
    virtual ~Piece(){}
    int getcoordY()const;
    int getcoordX()const;
    char getname()const;
    void setcoordY(int j);
    void setcoordX(int i);
    bool operator==(const Piece& other)const;
    void tolowercase();
    void virtual calculateMoves()=0;
    void addMove(char to,int coord_x,int coord_y);
};

Piece* createPiece(char name,int x,int y);

//-----Move függvények-----
bool checkAndAddMove(Game* game, Piece* from, int posX, int posY);

//Észak,dél,kelet,nyugat
void upwards(Piece* from,Game* game);
void downwards(Piece* from,Game* game);
void rightwards(Piece* from,Game* game);
void leftwards(Piece* from,Game* game);

//ÉK,ÉNY,Dk,DNY
void diagonalUpRight(Piece* from, Game* game);
void diagonalUpLeft(Piece* from, Game* game);
void diagonalDownRight(Piece* from, Game* game);
void diagonalDownLeft(Piece* from, Game* game);

//Az előzők kombinálva


void orthogonal(Piece* from, Game* game);
void diagonal(Piece* from, Game* game);

//Különleges lépésmódok
void pawnmove(Piece* from, Game* game);
void horsemove(Piece* from, Game* game);
void kingmove(Piece* from, Game* game);

//-----Move függvények-----

#endif //NHF_REFORMED_PIECE_H