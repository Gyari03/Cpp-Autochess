#ifndef NHF_REFORMED_MOVE_H
#define NHF_REFORMED_MOVE_H

class Piece;

class Move {
private:
    Piece* from;
    int x, y;
    char to;
    int weight;

public:
    Move(Piece* originPiece, int coordX, int coordY, char destinationPieceName=0);
    ~Move();
    void calculateWeight();
    bool operator>(const Move& otherMove) const;
    Piece* getPiece()const;
    int getCoordX()const;
    int getCoordY()const;
    int getWeight()const;
};
#endif //NHF_REFORMED_MOVE_H