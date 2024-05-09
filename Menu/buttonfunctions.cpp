#include "menu.h"
#include "buttonfunctions.h"
#include "../Ui/uiMenu.h"
#include "../Ui/uiEditor.h"
#include <iostream>
#include <fstream>
#include "../List/List.hpp"
#include "../Game/Army.h"
#include "../Game/Piece.h"
#include "../File Management/Filemanagement.h"
#include "../Game/Game.h"
#include "../Ui/uiGame.h"


#include "../Memtrace/memtrace.h"

Menu* MainMenu() {
    Menu* main=new Menu;
    main->newButton(Button("Play", main->getIdCounter(), &Play));
    main->newButton(Button("Exit", main->getIdCounter(), &Exit));
    return main;
}

void Play() {
    Menu* play=new Menu;
    play->newButton(Button("New game",play->getIdCounter(),&NewGame));
    play->newButton(Button("Army editor",play->getIdCounter(),&ArmyMenu));
    Run(play);
}

void Exit() {
   exit(0);
}

void NewGame(){
    //Leírása:
    //Kiválaszt mindkét oldalra 1-1 sereget, amik be lesznek töltve 1-1 army regiszterbe
    //start parancsra elkezdődik a játék
    Army* reg1=new Army;
    Army* reg2=new Army;
    Menu* newgame = new Menu;
    newgame->newButton(Button("Team1",newgame->getIdCounter(),&ChooseArmy,reg1));
    newgame->newButton(Button("Team2",newgame->getIdCounter(),&ChooseArmy,reg2));
    newgame->newButton(Button("Play game",newgame->getIdCounter(),&Gamesz,reg1,reg2));
    Run(newgame);

    //memóriafelszabadítása
    delete reg1;
    delete reg2;

}

void ArmyMenu(){
    Menu* army=new Menu;
    army->newButton(Button("Create new army",army->getIdCounter(),&CreateArmy));
    List<Army> armies = ListofArmies("armies.txt");
    for(int i =0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
       army->newButton(Button(currentArmy->getnameofArmy(),army->getIdCounter(),&EditArmy,currentArmy));

    }
    refreshingRun(army);
}

void CreateArmy(){
    Editor newEditor;
    Run(&newEditor);
}

void EditArmy(Army* army){
    Army* temp = new Army; //a seregeket a heapre akarjuk
    Army::copyArmy(army,temp);
    Editor newEditor(temp);
    Run(&newEditor);
}

void ChooseArmy(Army* reg){
    Menu* choice = new Menu;
    List<Army> armies = ListofArmies("armies.txt");
    for(int i=0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
        choice->newButton(Button(currentArmy->getnameofArmy(),choice->getIdCounter(),&Army::copyArmy,currentArmy,reg));
    }
    Run(choice);
}

void Gamesz(Army* reg1,Army* reg2){
    Game* game = new Game(reg1,reg2);
    Run(game);
}