#include "Game.h"
#include "../List/List.hpp"

Game::Game():turn(true){
    for(size_t i=0;i<2;i++){
        team[i]=nullptr;
    }
    computer = Computer(team[0],team[1]);
}

Game::Game(Army* white,Army* black):white(*white),black(*black),turn(true){
    team[0] = new Team(white,White);
    team[1] = new Team(black,Black);
    computer  = Computer(team[0],team[1]);
}

bool Game::getTurn() const {
    return turn;
}

Piece* Game::searchfor(int x, int y) {
    if(team[0]->getArmy()->getPiece(x,y)!=nullptr){
        return  team[0]->getArmy()->getPiece(x,y);
    }
    if(team[1]->getArmy()->getPiece(x,y)!=nullptr){
        return team[1]->getArmy()->getPiece(x,y);
    }
    return nullptr;
}

Team* Game::getTeam(size_t a){
    if(a>2){return nullptr;}
    return team[a];
}

TeamColor Game::getColorOfPiece(Piece *piece) { //csak úgy hasdználjuk hogy fix benne legyen a játékban
    if(this->team[0]->getArmy()->partOfArmy(piece)){return White;}
    else{return Black;}
}//throw probléma ha nem találja

bool Game::occupied(int x,int y) {
    if(this->team[0]->getArmy()->getPiece(x,y)!=nullptr){
        return true;
    }
    if(this->team[1]->getArmy()->getPiece(x,y)!=nullptr){
        return true;
    }
    return false;
}

void Game::collectTeamMoves() {  //Basically meg lett oldva, useless lett mert már a calculateMovesban meg van oldva
    //Csapat beállítása
    Team* currentTeam;
    if(turn){ currentTeam = team[0];}
    else{ currentTeam = team[1];}

    //Változók létrehozása
    List<Move> TeamMoves = currentTeam->getTeamMoves();
    List<Move> currentPieceMoves;

    //Az összes bábu lépéseinek a beleolvasztása a csapatlistába
    for(int i=0; i < currentTeam->getArmy()->getsizeofArmy(); i++){
       currentPieceMoves = currentTeam->getArmy()->getPiece(i)->getMoves();
        TeamMoves.consumeList(currentPieceMoves);
    }
}
//------------
//Computer: calculatemove,decide move
//Game: makemove
//------------- A computer gondolkodik, a game cselekszik

void Game::makeMove() {
//computer.calculateMoves(this); ezt nem itt kell megoldani //összesítsd majd egy nagyobb fv.-ben
    Move* move = computer.decideMove(this);
    Piece* from = move->getPiece();
    TeamColor fromColor = this->getColorOfPiece(from);

    //Ellenséges+szöv csapat megállapítása
    Team* enemy;
    Team* ally;
    if(fromColor==White){enemy = team[1];ally = team[0];}
    else{enemy = team[0];ally = team[1];}

    //X és Y coordináták
    int coord_X = move->getX();
    int coord_Y = move->getY();

    if(this->occupied(coord_X,coord_Y)){
        enemy->getArmy()->deletePiece(coord_X,coord_Y);
    }
    from->setcoordX(coord_X);
    from->setcoordY(coord_Y);

    //Csapat lépések kiűrítése
    ally->getTeamMoves().clear();

}

void Game::playRound() {
    computer.calculateMoves(this);
    makeMove();
    turn = !turn; //kör átadása
}
