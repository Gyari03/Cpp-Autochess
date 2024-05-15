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
    main.addButton(Button("Play \n0)Exit", main.getIdCounter(), &Play));
    uiMenu::Run(&main);
}

void ButtonFunctions::Play() {
    Menu play;
    play.addButton(Button("New game", play.getIdCounter(), &NewGame));
    play.addButton(Button("Army editor", play.getIdCounter(), &ArmyMenu));
    uiMenu::Run(&play);
}

void ButtonFunctions::NewGame(){
    Army reg1;
    Army reg2;
    Menu newgame;
    newgame.addButton(Button("Team1", newgame.getIdCounter(), &ChooseArmy, &reg1));
    newgame.addButton(Button("Team2", newgame.getIdCounter(), &ChooseArmy, &reg2));
    newgame.addButton(Button("Play game", newgame.getIdCounter(), &PlayMatch, &reg1, &reg2));
    uiMenu::Run(&newgame);
}

void ButtonFunctions::ArmyMenu(){
    Menu army;
    army.addButton(Button("Create new army", army.getIdCounter(), &CreateArmy));
    List<Army> armies = Filemanagement::ListofArmies("armies.dat");
    for(int i = 0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
        army.addButton(Button(currentArmy->getnameofArmy(), army.getIdCounter(), &EditArmy, currentArmy));

    }
    uiMenu::refreshingRun(&army);
}

void ButtonFunctions::CreateArmy(){
    Editor newEditor;
    uiEditor::Run(&newEditor);
}

void ButtonFunctions::EditArmy(Army* army){
    Army* temp = new Army;
    Army::copyArmy(army,temp);
    Editor newEditor(temp);
    uiEditor::Run(&newEditor);
}

void ButtonFunctions::ChooseArmy(Army* reg){
    Menu choice;
    List<Army> armies = Filemanagement::ListofArmies("armies.dat");
    for(int i=0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
        choice.addButton(Button(currentArmy->getnameofArmy(), choice.getIdCounter(), &Army::copyArmy, currentArmy, reg));
    }
    uiMenu::Run(&choice);
}

void ButtonFunctions::PlayMatch(Army* reg1, Army* reg2){
    Game game = Game(reg1,reg2);
    uiGame::Run(&game);
}