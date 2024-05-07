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
    }
    Game(Army white,Army black);//rendes létrehozás
    void setupBoard();
    Piece* searchfor(int x,int y){
        Piece* proba = createPiece('K',1,2);
        return proba;
    }

};


#endif //NHF_REFORMED_GAME_H
