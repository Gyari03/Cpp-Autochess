#ifndef NHF_REFORMED_MOVE_H
#define NHF_REFORMED_MOVE_H

class Piece;

class Move {
private:
    Piece* from;
    int x, y; //to
    char to;
    int weight;

public:
    Move(Piece* from,int x,int y,char to=0);
    ~Move();
    void calculateweight();
    bool operator>(const Move& other) const;
   // bool operator<(const Move& other) const;
   // bool operator==(const Move& other) const;
};


#endif //NHF_REFORMED_MOVE_H
