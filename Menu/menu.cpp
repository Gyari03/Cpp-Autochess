#include "menu.h"
#include <iostream>

Menu::Menu():idCounter(0),buttons(nullptr),exit(false){}

Menu::~Menu(){
    delete[] buttons;
}

void Menu::incrementCounter() {
    idCounter++;
}

void Menu::updateExit() { //csak az exit gombnak
    exit=true;
}

void Menu::newButton(const Button& extra) {
    this->incrementCounter();
    if(idCounter==1){
        this->buttons=new Button[idCounter];
        this->buttons[0]=extra; //copyconstructor illetve egyenloseg
        buttons[0].setId(idCounter);
        return;
    }
    Button *updatedButtons = new Button[idCounter];
    for(unsigned int i=0;i<idCounter-1;i++){
        updatedButtons[i]=this->buttons[i]; //egyenlosegoperator?
    }
    updatedButtons[idCounter-1]=extra;
    updatedButtons[idCounter-1].setId(idCounter);
    delete[] this->buttons;
    this->buttons=updatedButtons;
}

Button* Menu::getButton(int idx)const{
    return &buttons[idx];
}

bool Menu::getExit()const{
    return exit;//returnoli exit bool értékét
}
