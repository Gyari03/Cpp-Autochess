#include "Game.h"

Game::Game(){
    for(size_t i=0;i<2;i++){
        team[i]=nullptr;
    }
    computer = Computer(team[0],team[1]);
}

Game::Game(Army* white,Army* black):white(*white),black(*black){
    team[0] = new Team(white,White);
    team[1] = new Team(black,Black);
    computer  = Computer(team[0],team[1]);
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
    if(this->team[0]->getArmy()->getPiece(x,y)!=nullptr){
        return true;
    }
    return false;
}

void Game::collectTeamMoves() {

}