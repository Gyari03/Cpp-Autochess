#include "Team.h"
#include <random>
#include "../Memtrace/memtrace.h"

Team::Team(Army* army,TeamColor color):teamColor(color){
    ownArmy = new Army;
    Army::copyArmy(army,ownArmy);
    if(teamColor == Black){
        Army::mirrorArmy(ownArmy);
    }
}

Team::~Team(){

}

Army* Team::getArmy()  {
    return ownArmy;
}


List<Move>& Team::getTeamMoves() {
    return teamMoves;
}

Move* Team::getRandomMove() {
    int size = teamMoves.getSize();
    int randIdx = rand() % size;
    return teamMoves[randIdx];
}

int Team::countAmountOfKigns() {
    int ret = 0;
    for(int i=0;i<ownArmy->getsizeofArmy();i++){
        char temp = ownArmy->getPiece(i)->getname();
        if(temp == 'k' || temp == 'K'){ret++;}
    }
    return ret;
}
