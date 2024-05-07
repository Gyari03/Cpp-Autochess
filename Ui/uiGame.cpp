#include "uiGame.h"

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
    int count_Y=8;
    for(int y=0;y<8;y++){
        if(y<4 ){
            continue;
        }
        for(int i=0;i<8;i++){ //így nézett ki:         for(int i=0;i<4;i++){
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
                        std::cout<<"  "<<count_Y--;
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
    // Implementation of show function
}

bool uiGame::input() {
    // Implementation of input function
    return false;
}

void uiGame::idle() {
    // Implementation of idle function
}
