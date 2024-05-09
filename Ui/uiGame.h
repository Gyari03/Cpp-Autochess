#ifndef NHF_REFORMED_UIGAME_H
#define NHF_REFORMED_UIGAME_H
#include "ui.h"
#include "../Game/Game.h"
#include <iostream>
class uiGame:public ui {
private:
    Game* game;
public:
    uiGame(Game* game);
    ~uiGame();
    void show() override;
    bool input() override;
    void renderTable();
    void idle() override;
    void endScreen();
    static void Run(Game* gameptr);
    static void delayMilliseconds(unsigned int ms);
};

#endif //NHF_REFORMED_UIGAME_H
