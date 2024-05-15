#include "uiMenu.h"
#include "../Exception/Error.h"
#include "../Memtrace/memtrace.h"

uiMenu::uiMenu(Menu *menu,std::ostream& os,std::istream& is):ui(os,is),menu(menu) {}

uiMenu::~uiMenu(){}

void uiMenu::display(){
    this->clearScreen();
    for(size_t i=0;i<menu->getIdCounter();i++){
        os<<menu->getButton(i)->getId()<<")"<<menu->getButton(i)->getName()<<std::endl;
    }
}

bool uiMenu::handleInput(){ //returnérték:bool-> true:lejátszott függvény||false:hibás bemenet, nem játszott le függvényt, amit csak a refreshingidle-ben használunk fel.


    std::string inputBuffer; //Azért string inputBuffer és nem egyből size_t-be rakjuk, mivel ha a felhasználó nem számot ír be akkor a program leáll. Ezért ezzel próbálom kikerülni.
    size_t choice;
    is>>inputBuffer;

    for(char i:inputBuffer){
        if (!isdigit(i)) {throw Error("Invalid button choice input");}
    }

    choice = std::stoi(inputBuffer);

    if(choice==0){
        menu->updateExit();
        return false;
    }
    //hibás bemenet esetén:
    else if(choice>menu->getIdCounter() || choice<0){
        //return false;
        throw Error("Invalid button index");
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
        } catch (const std::exception &e) {os << "Error:" << e.what() << std::endl;}
    }
}

void uiMenu::refreshingidle() {
    display();

    while(!(menu->getExit())){
        try{
            if(handleInput()){menu->updateExit();} //handleInput mellékhatása egy bool
            display();
        }catch (const std::exception &e) {os << "Error:" << e.what() << std::endl;}
    }
}


void uiMenu::refreshingRun(Menu* menuPtr,std::ostream& os,std::istream& is){
        uiMenu menu(menuPtr,os,is);
        menu.refreshingidle();
}

void uiMenu::Run(Menu* menuPtr,std::ostream& os,std::istream& is){
    uiMenu menu(menuPtr,os,is);
    menu.idle();
}