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



//------------
Menu* MainMenu() {
    Menu* main=new Menu;
    main->newButton(Button("Play", main->getIdCounter(), &Play));
   // main->newButton(Button("Settings", main->getIdCounter(), &Settings));
    main->newButton(Button("Exit", main->getIdCounter(), &Exit));
    return main;
}
//------------

//Main menu
void Play() {
    Menu* play=new Menu;
    play->newButton(Button("New game",play->getIdCounter(),&NewGame));
    play->newButton(Button("Army editor",play->getIdCounter(),&ArmyMenu));
    Run(play);

}
/*
void Settings() {
    Menu* settings=new Menu;
    settings->newButton(Button("Change color",settings->getIdCounter(),&SetColor));
    //settings->idle();
    Run(settings);
}*/

void Exit() {
   exit(0);
}
//------------


//Play menu
void NewGame(){
    std::cout << "New game!!";
}

void ArmyMenu(){
    Menu* army=new Menu;
    army->newButton(Button("Create new army",army->getIdCounter(),&CreateArmy));
    List<Army>* armies = ListofArmies("armies.txt");
    for(int i =0;i<armies->getSize();i++){
        Army* currentArmy = (*armies)[i];
       army->newButton(Button(currentArmy->getnameofArmy(),army->getIdCounter(),&EditArmy,currentArmy));
    }
    refreshingRun(army);
    delete armies;
}
//------------


//Settings menu
/*
void SetColor(){
    std::cout<<"NEW COLOR!"<<std::endl;
}
*/

void CreateArmy(){
    Editor* newEditor = new Editor;
    Run(newEditor);
}

void EditArmy(Army* army){
    Editor* newEditor = new Editor(army);
    Run(newEditor);

}

//------------