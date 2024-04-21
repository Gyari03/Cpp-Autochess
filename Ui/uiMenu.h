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
    bool input() override;
    void idle() override;
    void refreshingidle();
};

void Run(Menu* menu);
void refreshingRun(Menu* menuPtr);


#endif //NHF_REFORMED_UIMENU_H
