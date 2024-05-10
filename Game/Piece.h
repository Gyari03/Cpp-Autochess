#ifndef NHF_REFORMED_PIECE_H
#define NHF_REFORMED_PIECE_H
#include "../List/List.hpp"
#include "Move.h"

class Game;

class Piece {
private:
    int y,x;
    char name;

protected:
    List<Move> piece_moves;

public:
    Piece(char name, int coordX=0, int coordY=0);
    virtual ~Piece(){}
    int getCoordY()const;
    int getCoordX()const;
    char getName()const;
    List<Move>& getMoves();
    void setCoordY(int newY);
    void setCoordX(int newX);
    bool operator==(const Piece& otherPiece)const;
    void toLowercase();
    void virtual calculateMoves(Game* game)=0;
    void addMove(char destinationPieceName, int coordX, int coordY);
    static Piece* createPiece(char name,int x,int y);
    static bool checkAndAddMove(Game* game, Piece* originPiece, int posX, int posY);
    static void upwards(Piece* originPiece, Game* game);//Észak,dél,kelet,nyugat
    static void downwards(Piece* originPiece, Game* game);
    static void rightwards(Piece* originPiece, Game* game);
    static void leftwards(Piece* originPiece, Game* game);
    static void diagonalUpRight(Piece* originPiece, Game* game);//ÉK,ÉNY,DK,DNY
    static void diagonalUpLeft(Piece* originPiece, Game* game);
    static void diagonalDownRight(Piece* originPiece, Game* game);
    static void diagonalDownLeft(Piece* originPiece, Game* game);
    static void orthogonal(Piece* originPiece, Game* game);//Az előzők kombinálva
    static void diagonal(Piece* originPiece, Game* game);
    static void pawnMove(Piece* originPiece, Game* game);//Különleges lépésmódok
    static void horseMove(Piece* originPiece, Game* game);
    static void kingMove(Piece* originPiece, Game* game);
};
#endif //NHF_REFORMED_PIECE_H