#include "Editor.h"

Editor::Editor() {
    this->army = new Army;
}

Editor::Editor(Army *army) {
    this->army=army;
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