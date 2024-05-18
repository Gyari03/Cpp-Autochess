#include "uiGame.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "../Memtrace/memtrace.h"

uiGame::uiGame(Game *game,std::ostream& os,std::istream& is):ui(os,is),game(game) {}

uiGame::~uiGame(){}

void uiGame::renderTable() {
    for(int i=0;i<8;i++){
        if(i!=0){
            os<<"         "<<i+1;
        }
        else{
            os<<"     "<<i+1;
        }
    }
    os<<std::endl;
    for(int y=0;y<8;y++){
        for(int i=0;i<4;i++){
            os<<"#";
            if(i%4==0){
                for(int j=0;j<8;j++){
                    os<<" # # # # #";
                }
                os<<std::endl;
            }
            else if(i%4==1 || i%4==3){
                for(int j=0;j<8;j++){
                    os<<"         #";
                }
                os<<std::endl;
            }
            else if(i%4==2){
                for(int j=0;j<8;j++){ //destinationX+1 és 8-destinationY a konvertálandóak
                    if(game->searchFor(j + 1, 8 - y) != nullptr){
                        os << "    " << game->searchFor(j + 1, 8 - y)->getName() << "    #";
                    }
                    else if(game->searchFor(j + 1, 8 - y) == nullptr){
                        os<<"         #";
                    }

                    if(j==7){ //Y koordináta számozás
                        os<<"  "<<8-y;
                    }
                }
                os<<std::endl;
            }
        }
        if(y==7){
            os<<"#";
            for(int j=0;j<8;j++){
                os<<" # # # # #";
            }
        }
    }
    os<<std::endl;
}


void uiGame::display() {
    clearScreen();
    renderTable();
}

bool uiGame::handleInput() {
    this->game->playRound();
    return false;
}

void uiGame::idle() {
    while(!game->getEnd()){ //while(game_end!=true){...}
        display();
        handleInput();
        #ifndef CPORTA
            delayMilliseconds(1000);
        #else
            delayMilliseconds(10);
        #endif
    }
    endScreen();
}


void uiGame::Run(Game* gameptr,std::ostream& os,std::istream& is){
    uiGame game(gameptr,os,is);
    game.idle();
}

void uiGame::endScreen() {
    clearScreen();
    GameResult end = game->getResult();
    if(end == DRAW) {
        os<<"Stalemate! The game ends in a draw.";
    }
    else if(end == TEAM1_WIN){
        os<<"Team 1 Wins!";
    }
    else{
        os<<"Team 2 Wins!";
    }
    #ifndef CPORTA
        delayMilliseconds(8000);
    #else
        delayMilliseconds(100);
    #endif
}