#include "Editor.h"

Editor::Editor() {
    this->army = new Army;
    this->exit=false;
    this->toDelete=false;
}

Editor::Editor(Army *army) {
    this->army=army; //ügyelj arra, hogy csak dinamikusan foglalt sereget kapjon
    this->exit=false;
    this->toDelete=false;
}

Army* Editor::getArmy() {
    return army;
}

Piece* Editor::searchfor(int x,int y){
    return army->getPiece(x,y);
}

void Editor::updateExit() {
    exit = true;
}

bool Editor::getExit() const {
    return exit;
}

void Editor::updateDelete() {
    toDelete=true;
}

bool Editor::getDelete() const {
    return toDelete;
}

void Editor::saveArmy() {
    AppendArmy(army,"armies.txt");
}

void Editor::editArmy() {
    EditArmy(army,"armies.txt");
}