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
    void display() override;
    bool handleInput() override;
    void renderTable();
    void idle() override;
    void endScreen();
    static void Run(Game* gameptr);
};
#endif //NHF_REFORMED_UIGAME_H