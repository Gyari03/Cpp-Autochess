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

//(std::ostream& os,std::istream& is)

void ButtonFunctions::MainMenu(std::ostream& os,std::istream& is) {
    Menu main;
    main.addButton(Button("Play\n0)Exit", main.getIdCounter(), &Play,os,is));
    uiMenu::Run(&main,os,is);
}

void ButtonFunctions::Play(std::ostream& os,std::istream& is) {
    Menu play;
    play.addButton(Button("New game", play.getIdCounter(), &NewGame,os,is));
    play.addButton(Button("Army editor", play.getIdCounter(), &ArmyMenu,os,is));
    uiMenu::Run(&play,os,is);
}

void ButtonFunctions::NewGame(std::ostream& os,std::istream& is){
    Army reg1;
    Army reg2;
    Menu newgame;
    newgame.addButton(Button("Team1", newgame.getIdCounter(), &ChooseArmy, &reg1,os,is));
    newgame.addButton(Button("Team2", newgame.getIdCounter(), &ChooseArmy, &reg2,os,is));
    newgame.addButton(Button("Play game", newgame.getIdCounter(), &PlayMatch, &reg1, &reg2,os,is));
    uiMenu::Run(&newgame,os,is);
}

void ButtonFunctions::ArmyMenu(std::ostream& os,std::istream& is){
    Menu army;
    army.addButton(Button("Create new army", army.getIdCounter(), &CreateArmy,os,is));
    List<Army> armies = Filemanagement::ListofArmies("armies.dat");
    for(int i = 0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
        army.addButton(Button(currentArmy->getnameofArmy(), army.getIdCounter(), &EditArmy, currentArmy,os,is));

    }
    uiMenu::refreshingRun(&army,os,is);
}

void ButtonFunctions::CreateArmy(std::ostream& os,std::istream& is){
    Editor newEditor;
    uiEditor::Run(&newEditor,os,is);
}

void ButtonFunctions::EditArmy(Army* army,std::ostream& os,std::istream& is){
    Army* temp = new Army;
    Army::copyArmy(army,temp);
    Editor newEditor(temp);
    uiEditor::Run(&newEditor,os,is);
}

void ButtonFunctions::ChooseArmy(Army* reg,std::ostream& os,std::istream& is){
    Menu choice;
    List<Army> armies = Filemanagement::ListofArmies("armies.dat");
    for(int i=0;i<armies.getSize();i++){
        Army* currentArmy = armies[i];
        choice.addButton(Button(currentArmy->getnameofArmy(), choice.getIdCounter(), &Army::copyArmy, currentArmy, reg,os,is));
    }
    uiMenu::Run(&choice,os,is);
}

void ButtonFunctions::PlayMatch(Army* reg1, Army* reg2,std::ostream& os,std::istream& is){
    Game game = Game(reg1,reg2);
    uiGame::Run(&game,os,is);
}

void ButtonFunctions::tesztfuggveny(std::ostream &os,std::istream& is) {
    os<<"Lefutottam!";
}