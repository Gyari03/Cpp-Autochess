#ifndef NHF_REFORMED_UIMENU_H
#define NHF_REFORMED_UIMENU_H

#include "../Menu/menu.h"
#include "ui.h"

class uiMenu:public ui {
private:
    Menu* menu;

public:
    uiMenu(Menu* menu);
    ~uiMenu();
    void show() override;
    void input() override;
    void idle() override;
};

void Run(Menu* menu);


#endif //NHF_REFORMED_UIMENU_H
