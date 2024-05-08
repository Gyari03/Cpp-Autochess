#include "uiGame.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

uiGame::uiGame(Game *game):game(game) {}

uiGame::~uiGame(){
    delete game;
}

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
       // if(y<4 ){
       //     continue;
       // }
        for(int i=0;i<4;i++){ //így nézett ki:         for(int i=0;i<4;i++){
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
                for(int j=0;j<8;j++){ //x+1 és 8-y a konvertálandóak
                    if(game->searchfor(j+1,8-y)!=nullptr){
                        std::cout<<"    "<<game->searchfor(j+1,8-y)->getname()<<"    #";
                    }
                    else if(game->searchfor(j+1,8-y)==nullptr){
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


void uiGame::show() {
    clear();
    renderTable();
}

//nincs
bool uiGame::input() {
    //Majd a computer adja be az inputot, a felhasználó nem szól bele
    this->game->playRound();
    return false;
}

void uiGame::idle() {
    while(true){ //while(game_end!=true){...}
        show();
        input();
        sleepme(2000);
    }
}


void Run(Game* gameptr){
    uiGame game(gameptr);
    game.idle();
}


void sleepme(unsigned int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}