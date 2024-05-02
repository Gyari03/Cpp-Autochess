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
    Army* reg1=nullptr;
    Army* reg2=nullptr;
    Menu* newgame = new Menu;
    newgame->newButton(Button("Team1",newgame->getIdCounter(),&ChooseArmy,reg1));
    newgame->newButton(Button("Team2",newgame->getIdCounter(),&ChooseArmy,reg2));
    newgame->newButton(Button("Play game",newgame->getIdCounter(),&Game));

    Run(newgame);
}

void ArmyMenu(){
    Menu* army=new Menu;
    army->newButton(Button("Create new army",army->getIdCounter(),&CreateArmy));
    List<Army>* armies = ListofArmies("armies.txt");
    for(int i =0;i<armies->getSize();i++){
        Army* currentArmy = (*armies)[i];
       army->newButton(Button(currentArmy->getnameofArmy(),army->getIdCounter(),&EditArmy,currentArmy));

    }
    refreshingRun(army); //nevek refreshelésével foglalkozzon újratöltés helhyett
    delete armies;
}

void CreateArmy(){
    Editor* newEditor = new Editor;
    Run(newEditor);
}

void EditArmy(Army* army){
    Editor* newEditor = new Editor(army);
    Run(newEditor);

}

void ChooseArmy(Army* reg){
    Menu* choice = new Menu;
    List<Army>* armies = ListofArmies("armies.txt");
    for(int i=0;i<armies->getSize();i++){
        Army* currentArmy = (*armies)[i];
        choice->newButton(Button(currentArmy->getnameofArmy(),choice->getIdCounter(),&convert,currentArmy,reg));
    }
    Run(choice);
    delete armies;
}

void convert(Army* from,Army* to){
    to = from;
}


void Game(){
   // class Game* game = new class Game;
    //Run(game);
}