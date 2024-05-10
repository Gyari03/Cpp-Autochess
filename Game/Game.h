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
    Team* team[2];
    Computer computer;
    bool WhiteTurn;
    bool endOfGame;
    GameResult result;

public:
    Game();
    ~Game();
    Game(Army* white,Army* black);
    bool isWhiteTurn()const;
    bool getEnd()const;
    GameResult getResult()const;
    void updateEnd();
    Piece* searchFor(int x, int y);
    Team* getTeam(size_t a);
    TeamColor getColorOfPiece(Piece* piece);
    bool occupied(int x,int y);
    void makeMove();
    void playRound();
    void checkIfOver();
    void clearMovesBuffer();
};
#endif //NHF_REFORMED_GAME_H