#ifndef NHF_REFORMED_GAME_H
#define NHF_REFORMED_GAME_H
#include "Team.h"
#include "Army.h"
#include "Computer.h"

class Game {
private:
    Team* team[2];//Team pointerekből 2-őt tárol [0]:fehér [1]:fekete //A Gamekonstruktorból hozódik létre a 2 team a Team konstruktorokból(Army*,Szin)
    //A team nem biztos hogy kell hogy pointer legyen || vagy talán mégis hiszen dinamikusan akarjuk foglalni
    Army white;
    Army black;
    Computer computer;
    bool turn; //true=fehér,false=fekete turnje jön

public:
    Game();
    Game(Army* white,Army* black);
    Piece* searchfor(int x,int y);
    Team* getTeam(size_t a);
    TeamColor getColorOfPiece(Piece* piece);
    bool occupied(int x,int y);
    void collectTeamMoves();
};


#endif //NHF_REFORMED_GAME_H
