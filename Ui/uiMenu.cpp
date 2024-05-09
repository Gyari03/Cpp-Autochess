#include "uiMenu.h"
#include "../Memtrace/memtrace.h"

uiMenu::uiMenu(Menu *menu):menu(menu) {}

uiMenu::~uiMenu(){
    //delete menu;
}

void uiMenu::show(){
    this->clear();
    for(size_t i=0;i<menu->getIdCounter();i++){
        std::cout<<menu->getButton(i)->getId()<<")"<<menu->getButton(i)->getName()<<std::endl;
    }
}

bool uiMenu::input(){ //returnérték: bool->true:lejátszott függvényt false:hibás bemenet, nem játszott le függvényt:amit csak a refreshingidle-ben használunk fel
    size_t choice;
    std::cin>>choice;
    if(choice==0){
        menu->updateExit();
        return false;
    }
    //hibás bemenet esetén:
    else if(choice>menu->getIdCounter() || choice<0){
        return false;
    }
    ButtonFunction function = menu->getButton(choice-1)->getFunction();
    function.execute();
    return true;
}

void uiMenu::idle(){
    while(!(menu->getExit())){
        show();
        input();
    }
}

void uiMenu::refreshingidle() {
    while(!(menu->getExit())){
        show();
        if(input()){menu->updateExit();} //input mellékhatása egy bool
    }
}

void uiMenu::refreshingRun(Menu* menuPtr){
        uiMenu menu(menuPtr);
        menu.refreshingidle();
}

void uiMenu::Run(Menu* menuPtr){
    uiMenu menu(menuPtr);
    menu.idle();
}