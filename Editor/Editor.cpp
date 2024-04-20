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