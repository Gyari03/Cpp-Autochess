#include "uiGame.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "../Memtrace/memtrace.h"

uiGame::uiGame(Game *game):game(game) {}

uiGame::~uiGame(){}

void uiGame::renderTable() {
    for(int i=0;i<8;i++){
        if(i!=0){
            std::cout<<"         "<<i+1;
        }
        else{
            std::cout<<"     "<<i+1;
        }
    }
    std::cout<<std::endl;
    for(int y=0;y<8;y++){
        for(int i=0;i<4;i++){
            std::cout<<"#";
            if(i%4==0){
                for(int j=0;j<8;j++){
                    std::cout<<" # # # # #";
                }
                std::cout<<std::endl;
            }
            else if(i%4==1 || i%4==3){
                for(int j=0;j<8;j++){
                    std::cout<<"         #";
                }
                std::cout<<std::endl;
            }
            else if(i%4==2){
                for(int j=0;j<8;j++){ //destinationX+1 és 8-destinationY a konvertálandóak
                    if(game->searchFor(j + 1, 8 - y) != nullptr){
                        std::cout << "    " << game->searchFor(j + 1, 8 - y)->getName() << "    #";
                    }
                    else if(game->searchFor(j + 1, 8 - y) == nullptr){
                        std::cout<<"         #";
                    }

                    if(j==7){ //Y koordináta számozás
                        std::cout<<"  "<<8-y;
                    }
                }
                std::cout<<std::endl;
            }
        }
        if(y==7){
            std::cout<<"#";
            for(int j=0;j<8;j++){
                std::cout<<" # # # # #";
            }
        }
    }
    std::cout<<std::endl;
}


void uiGame::display() {
    clearScreen();
    renderTable();
}

//nincs
bool uiGame::handleInput() {
    //Majd a computer adja be az inputot, a felhasználó nem szól bele
   // game->checkIfOver();

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


void uiGame::Run(Game* gameptr){
    uiGame game(gameptr);
    game.idle();
}

void uiGame::endScreen() {
    clearScreen();
    GameResult end = game->getResult();
    if(end == DRAW) {
        std::cout<<"Stalemate! The game ends in a draw.";
    }
    else if(end == TEAM1_WIN){
        std::cout<<"Team 1 Wins!";
    }
    else{
        std::cout<<"Team 2 Wins!";
    }
    #ifndef CPORTA
        delayMilliseconds(8000);
    #else
        delayMilliseconds(100);
    #endif
}