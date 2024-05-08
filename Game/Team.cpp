#include "Team.h"

Team::Team(Army* army,TeamColor color):teamColor(color){
    ownArmy = new Army;
    copyArmy(army,ownArmy);
    if(teamColor == Black){
        mirrorArmy(ownArmy);
    }
}

Army* Team::getArmy() const {
    return ownArmy;
}