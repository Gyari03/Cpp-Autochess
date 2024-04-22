#ifndef NHF_REFORMED_MOVE_H
#define NHF_REFORMED_MOVE_H

class Piece;

class Move {
private:
    Piece* from;
    int x, y; //to
    int weight;

public:
    void calcWeight();

};


#endif //NHF_REFORMED_MOVE_H
