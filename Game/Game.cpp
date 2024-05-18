#include "Game.h"
#include "../List/List.hpp"

Game::Game(): WhiteTurn(true), endOfGame(false), result(DRAW){
    for(size_t i=0;i<2;i++){
        team[i]=nullptr;
    }
    computer = Computer();
}

Game::Game(Army* white,Army* black): WhiteTurn(true), endOfGame(false), result(DRAW){
    team[0] = new Team(white,White);
    team[1] = new Team(black,Black);
    computer  = Computer();
}

Game::~Game(){
    delete team[0];
    delete team[1];
}

bool Game::isWhiteTurn() const {
    return WhiteTurn;
}

bool Game::getEnd() const {
    return endOfGame;
}

GameResult Game::getResult() const {
    return result;
}

void Game::updateEnd() {
    endOfGame= !endOfGame;
}

Piece* Game::searchFor(int x, int y) {
    if(team[0]->getArmy()->getPiece(x,y)!=nullptr){
        return  team[0]->getArmy()->getPiece(x,y);
    }
    if(team[1]->getArmy()->getPiece(x,y)!=nullptr){
        return team[1]->getArmy()->getPiece(x,y);
    }
    return nullptr;
}

Team* Game::getTeam(size_t idx){
    if(idx >= 2){return nullptr;}
    return team[idx];
}

TeamColor Game::getColorOfPiece(Piece *piece) { //csak úgy használjuk hogy fix benne legyen a játékban
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

void Game::makeMove() {
    Move* move = computer.decideMove(this);
    Piece* from = move->getPiece();
    TeamColor fromColor = this->getColorOfPiece(from);

    //Ellenséges+szöv csapat megállapítása
    Team* enemy;
    Team* ally;
    if(fromColor==White){enemy = team[1];ally = team[0];}
    else{enemy = team[0];ally = team[1];}

    //X és Y coordináták
    int coord_X = move->getCoordX();
    int coord_Y = move->getCoordY();

    if(this->occupied(coord_X,coord_Y)){
        enemy->getArmy()->deletePiece(coord_X,coord_Y);
    }
    from->setCoordX(coord_X);
    from->setCoordY(coord_Y);

    //Csapat lépések kiűrítése
    ally->getTeamMoves().clear();

}

void Game::playRound() {
    computer.calculateMoves(this);
    checkIfOver(); //vége van-e, akkor skippeljünk ki
    if(!endOfGame){
        makeMove();
        WhiteTurn = !WhiteTurn; //kör átadása
    }
    else{
        clearMovesBuffer();
    }
}

void Game::checkIfOver() {
    //alapadatok
    Team* current;
    if(WhiteTurn){ current = team[0];}
    else{current=team[1];}

    //Ha egyik csapatban nincs király -> másik csapat a nyertes
    if(current->countAmountOfKings() == 0){
        if(current==team[0]){
            updateEnd();
            result = TEAM2_WIN;
            return;
        }
        else{
            updateEnd();
            result = TEAM1_WIN;
            return;
        }
    }

    //Ha a most jövő csapatnak 0 lépése maradt -> Döntetlen
    if(current->getTeamMoves().getSize()==0){updateEnd();}//result=DRAW alapérték
}

void Game::clearMovesBuffer() {
    Team* current;
    if(WhiteTurn){ current = team[0];}
    else{current=team[1];}
    current->getTeamMoves().clear();
}


