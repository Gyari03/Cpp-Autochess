#include "Computer.h"
#include "Game.h"

Computer::Computer():white(nullptr),black(nullptr){}
Computer::Computer(Team* white,Team* black):white(white),black(black){}

void Computer::calculateMoves(Game* game){
    //Megállapítani hogy melyik csapat turnje van
    Team* current;
    if(game->getTurn()){current=game->getTeam(0);}
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
    if(game->getTurn()){current=game->getTeam(0);}
    else{current = game->getTeam(1);}

    return current->getTeamMoves().Maximum(); //A legnagyobb súlyú lépés returnölése
}

