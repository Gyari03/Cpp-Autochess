#ifndef NHF_REFORMED_GAME_H
#define NHF_REFORMED_GAME_H
#include "Team.h"
#include "Army.h"
#include "Computer.h"

enum GameResult {
    TEAM1_WIN,
    TEAM2_WIN,
    DRAW  //alapvető helyzetben DRAW lesz amíg nem kap értéket
};

class Game {
private:
    Team* team[2];//Team pointerekből 2-őt tárol [0]:fehér [1]:fekete //A Gamekonstruktorból hozódik létre a 2 team a Team konstruktorokból(Army*,Szin)
    //A team nem biztos hogy kell hogy pointer legyen || vagy talán mégis hiszen dinamikusan akarjuk foglalni
    //Army white;
    //Army black;
    Computer computer;
    bool turn; //true=fehér,false=fekete turnje jön
    bool endOfGame;
    GameResult result;

public:
    Game();
    ~Game();
    Game(Army* white,Army* black);
    bool getTurn()const;
    bool getEnd()const;
    GameResult getResult()const;
    void updateEnd();
    Piece* searchfor(int x,int y);
    Team* getTeam(size_t a);
    TeamColor getColorOfPiece(Piece* piece);
    bool occupied(int x,int y);
    void collectTeamMoves(); //useless
    void makeMove();
    void playRound();
    void checkIfOver();
    void clearMovesBuffer();

};


#endif //NHF_REFORMED_GAME_H
