#include "uiMenu.h"
#include "../Memtrace/memtrace.h"
#include "../Exception/Error.h"

uiMenu::uiMenu(Menu *menu):menu(menu) {}

uiMenu::~uiMenu(){}

void uiMenu::display(){
    this->clearScreen();
    for(size_t i=0;i<menu->getIdCounter();i++){
        std::cout<<menu->getButton(i)->getId()<<")"<<menu->getButton(i)->getName()<<std::endl;
    }
}

bool uiMenu::handleInput(){ //returnérték:bool-> true:lejátszott függvény||false:hibás bemenet, nem játszott le függvényt, amit csak a refreshingidle-ben használunk fel.


    std::string inputBuffer; //Azért string inputBuffer és nem egyből size_t-be rakjuk, mivel ha a felhasználó nem számot ír be akkor a program leáll. Ezért ezzel próbálom kikerülni.
    size_t choice;
    std::cin>>inputBuffer;

    if (!isdigit(inputBuffer[0])) {throw Error("Invalid button choice input");}
    choice = inputBuffer[0] - '0';

    if(choice==0){
        menu->updateExit();
        return false;
    }
    //hibás bemenet esetén:
    else if(choice>menu->getIdCounter() || choice<0){
        return false;
    }
    ButtonFunctionHandler function = menu->getButton(choice - 1)->getFunction();
    function.execute();
    return true;
}

void uiMenu::idle() {
    display();

    while (!(menu->getExit())) {
        try {
            handleInput();
            display();
        } catch (const std::exception &e) {std::cout << "Error:" << e.what() << std::endl;}
    }
}

void uiMenu::refreshingidle() {
    while(!(menu->getExit())){
        display();
        if(handleInput()){menu->updateExit();} //handleInput mellékhatása egy bool
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