#include "uiMenu.h"

uiMenu::uiMenu(Menu *menu):ui(),menu(menu) {}

uiMenu::~uiMenu(){
    delete menu;
}

void uiMenu::show(){
    this->clear();
    for(int i=0;i<menu->getIdCounter();i++){
        std::cout<<menu->getButton(i)->getId()<<")"<<menu->getButton(i)->getName()<<std::endl;
    }
}

void uiMenu::input(){
    int choice;
    std::cin>>choice;
    if(choice==0){
        menu->updateExit();
        return;
    }
    //átalakítani
    ButtonFunction function = menu->getButton(choice-1)->getFunction();
    function.execute();
}

//refresh menu->újratölti a menüt és kilvassa újra az adatokat


void uiMenu::idle(){
    while(!(menu->getExit())){
        show();
        input();
    }
}

void Run(Menu* menuPtr){
    uiMenu menu(menuPtr);
    menu.idle();
}