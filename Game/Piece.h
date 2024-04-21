#ifndef NHF_REFORMED_PIECE_H
#define NHF_REFORMED_PIECE_H
#include "../List/List.hpp"
#include "Move.h"


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
    void setcoordY(int x);
    void setcoordX(int y);
    bool operator==(const Piece& other)const;
    void tolowercase();
    void virtual calculateMoves()=0;
};


Piece* createPiece(char name,int x,int y);

#endif //NHF_REFORMED_PIECE_H
