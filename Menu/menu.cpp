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
    for(int i=0;i<idCounter-1;i++){
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

/*

void Menu::clear() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Menu::show(){
    clear();
    for(int i=0;i<this->idCounter;i++){
        std::cout<<this->buttons[i].getId()<<")"<<this->buttons[i].getName()<<std::endl;
    }

}


void Menu::input(){
    int choice;
    std::cin>>choice;
    if(choice==0){exit=true;return;}
    void(*FunctionPtr)() =this->buttons[choice-1].getFunction();
    FunctionPtr();
}

void Menu::idle(){
    while(!exit){
        this->show();
        this->input();
    }
}
*/