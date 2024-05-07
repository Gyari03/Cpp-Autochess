#ifndef NHF_REFORMED_GAME_H
#define NHF_REFORMED_GAME_H
#include "Team.h"
#include "Army.h"
#include "Computer.h"

class Game {
private:
    Team* team[2];//Team pointerekből 2-őt tárol [0]:fehér [1]:fekete //A Gamekonstruktorból hozódik létre a 2 team a Team konstruktorokból(Army*,Szin)
    //A team nem biztos hogy kell hogy pointer legyen || vagy talán mégis hiszen dinamikusan akarjuk foglalni
    Army white;
    Army black;
    Computer computer;

public:
    Game(){
        for(size_t i=0;i<2;i++){
            team[i]=nullptr;
        }
        computer = Computer(team[0],team[1]);
    }
    Game(Army* white,Army* black):white(*white),black(*black){
        team[0] = new Team(white,White);
        team[1] = new Team(black,Black);
        computer  = Computer(team[0],team[1]);
    }
    Piece* searchfor(int x,int y){
        if(team[0]->getArmy()->getPiece(x,y)!=nullptr){
           return  team[0]->getArmy()->getPiece(x,y);
        }
        if(team[1]->getArmy()->getPiece(x,y)!=nullptr){
            return team[1]->getArmy()->getPiece(x,y);
        }
        return nullptr;
    }
};


#endif //NHF_REFORMED_GAME_H
