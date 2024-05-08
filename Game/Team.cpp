#include "Team.h"

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

