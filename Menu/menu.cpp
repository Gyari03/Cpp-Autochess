#include "menu.h"
#include <iostream>
#include "../Memtrace/memtrace.h"

Menu::Menu(): idCounter(0), buttonArray(nullptr), exitRequested(false){}

Menu::~Menu(){
    delete[] buttonArray;
}

void Menu::incrementCounter() {
    idCounter++;
}

void Menu::updateExit() { //csak az exitRequested gombnak
    exitRequested=!exitRequested;
}

void Menu::addButton(const Button& extra) {
    this->incrementCounter();
    if(idCounter==1){
        this->buttonArray=new Button[idCounter];
        this->buttonArray[0]=extra; 
        buttonArray[0].setId(idCounter);
        return;
    }
    Button *updatedButtons = new Button[idCounter];
    for(unsigned int i=0;i<idCounter-1;i++){
        updatedButtons[i]=this->buttonArray[i];
    }
    updatedButtons[idCounter-1]=extra;
    updatedButtons[idCounter-1].setId(idCounter);
    delete[] this->buttonArray;
    this->buttonArray=updatedButtons;
}

Button* Menu::getButton(int idx)const{
    return &buttonArray[idx];
}

bool Menu::getExit()const{
    return exitRequested;//returnoli exitRequested bool értékét
}

size_t Menu::getIdCounter()const{return idCounter;}