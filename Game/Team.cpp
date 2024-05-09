#include "Team.h"
//#include <random>

Team::Team(Army* army,TeamColor color):teamColor(color){
    ownArmy = new Army;
    copyArmy(army,ownArmy);
    if(teamColor == Black){
        mirrorArmy(ownArmy);
    }
}

Army* Team::getArmy()  {
    return ownArmy;
}


List<Move>& Team::getTeamMoves() {
    return teamMoves;
}
/*
List<Move> Team::getTeamMoves()const{
    return teamMoves;
}*/
/*
Move* Team::getRandomMove() {
    int size = teamMoves.getSize();
    int randIdx = rand() % size;
    return teamMoves[randIdx];
}*/
