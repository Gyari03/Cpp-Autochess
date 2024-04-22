#ifndef NHF_REFORMED_MENU_H
#define NHF_REFORMED_MENU_H

#include "button.h"
#include <iostream>
#include <cstddef>

class Menu{
private:
    unsigned int idCounter; //lehet hogy actually meretnek is lehet hasznalni
    Button* buttons;
    bool exit;
public:
    Menu();
    ~Menu();
    void incrementCounter();
    void updateExit();
    void newButton(const Button& extra);
    Button* getButton(int idx)const;
    bool getExit()const;
    unsigned int getIdCounter()const{return idCounter;}
};

#endif //NHF_REFORMED_MENU_H