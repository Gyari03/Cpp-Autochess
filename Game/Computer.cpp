#include "Computer.h"
#include "Game.h"
#include "../Memtrace/memtrace.h"

Computer::Computer(){}
void Computer::calculateMoves(Game* game){
    //Megállapítani hogy melyik csapat turnje van
    Team* current;
    if(game->isWhiteTurn()){ current=game->getTeam(0);}
    else{current = game->getTeam(1);}

    //Bábuk egyenkénti lépéseinek összeszámlálása
    for(int i=0;i<current->getArmy()->getsizeofArmy();i++){
        current->getArmy()->getPiece(i)->calculateMoves(game);

        //Lépések beszívása a csapat lépései közé
        current->getTeamMoves().consumeList(current->getArmy()->getPiece(i)->getMoves());
    }
}

Move* Computer::decideMove(Game *game) {
    Team* current;
    if(game->isWhiteTurn()){ current=game->getTeam(0);}
    else{current = game->getTeam(1);}
    Move* ret = current->getTeamMoves().Maximum();
    if(ret->getWeight()==0){ //A determinisztikusság megszüntetéséért felelős funkció
        ret = current->getRandomMove();
    }
    return ret;
}

