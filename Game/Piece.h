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



//Move függvények

void upwards(Piece* from,Game* game);

void vertical();













#endif //NHF_REFORMED_PIECE_H
