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



void ButtonFunctions::MainMenu() {
    Menu main;
    main.newButton(Button("Play", main.getIdCounter(), &Play));
    main.newButton(Button("Exit", main.getIdCounter(), &Exit));
    Run(&main);
}

void ButtonFunctions::Play() {
    Menu play;
    play.newButton(Button("New game",play.getIdCounter(),&NewGame));
    play.newButton(Button("Army editor",play.getIdCounter(),&ArmyMenu));
    Run(&play);
}

void ButtonFunctions::Exit() {
   exit(0);
}

void ButtonFunctions::NewGame(){
    Army reg1;
    Army reg2;
    Menu newgame;
    newgame.newButton(Button("Team1",newgame.getIdCounter(),&ChooseArmy,&reg1));
    newgame.newButton(Button("Team2",newgame.getIdCounter(),&ChooseArmy,&reg2));
    newgame.newButton(Button("Play game",newgame.getIdCounter(),&Gamesz,&reg1,&reg2));
    Run(&newgame);
}

void ButtonFunctions::ArmyMenu(){
    Menu army;
    army.newButton(Button("Create new army",army.getIdCounter(),&CreateArmy));
    List<Army> armies = Filemanagement::ListofArmies("armies.txt");
    for(int i = 0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
       army.newButton(Button(currentArmy->getnameofArmy(),army.getIdCounter(),&EditArmy,currentArmy));

    }
    refreshingRun(&army);
}

void ButtonFunctions::CreateArmy(){
    Editor newEditor;
    Run(&newEditor);
}

void ButtonFunctions::EditArmy(Army* army){
    Army* temp = new Army;
    Army::copyArmy(army,temp);
    Editor newEditor(temp);
    Run(&newEditor);
}

void ButtonFunctions::ChooseArmy(Army* reg){
    Menu choice;
    List<Army> armies = Filemanagement::ListofArmies("armies.txt");
    for(int i=0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
        choice.newButton(Button(currentArmy->getnameofArmy(),choice.getIdCounter(),&Army::copyArmy,currentArmy,reg));
    }
    Run(&choice);
}

void ButtonFunctions::Gamesz(Army* reg1,Army* reg2){
    Game game = Game(reg1,reg2);
    Run(&game);
}