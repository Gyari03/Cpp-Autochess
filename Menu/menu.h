#ifndef NHF_REFORMED_MENU_H
#define NHF_REFORMED_MENU_H

#include "button.h"
#include <iostream>
#include <cstddef>

class Menu{
private:
    size_t idCounter; //    unsigned int idCounter;
    Button* buttonArray;
    bool exitRequested;
public:
    Menu();
    ~Menu();
    void incrementCounter();
    void updateExit();
    void addButton(const Button& extra);
    Button* getButton(int idx)const;
    bool getExit()const;
    size_t getIdCounter()const; //    unsigned int getIdCounter()const{return idCounter;}
};

#endif //NHF_REFORMED_MENU_H