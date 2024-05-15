#include "Editor.h"
#include "../Memtrace/memtrace.h"

Editor::Editor() {
    this->army = new Army;
    this->exit=false;
    this->toDelete=false;
}

Editor::~Editor(){
    delete this->army;
};

Editor::Editor(Army *army) {
    this->army=army;
    this->exit=false;
    this->toDelete=false;
}

Army* Editor::getArmy()const {
    return army;
}

Piece* Editor::searchFor(int coordX, int coordY){
    return army->getPiece(coordX, coordY);
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
    Filemanagement::AppendArmy(army,"armies.dat");
}

void Editor::editArmy() {
    Filemanagement::EditArmy(army,"armies.dat");
}

void Editor::deleteArmy() {
    Filemanagement::DeleteArmy(army,"armies.dat");
}