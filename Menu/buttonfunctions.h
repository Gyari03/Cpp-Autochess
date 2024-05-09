#ifndef NHF_REFORMED_BUTTONFUNCTIONS_H
#define NHF_REFORMED_BUTTONFUNCTIONS_H
#include "../Game/Army.h"

class ButtonFunctions{
public:
    static void MainMenu();
    static void Play();
    static void Exit();
    static void NewGame();
    static void ArmyMenu();
    static void CreateArmy();
    static void EditArmy(Army*);
    static void ChooseArmy(Army*); //a paraméterként megkapott paraméter-be tölti majd be az armyt amit választ
    static void Gamesz(Army* reg1, Army* reg2);
};
#endif //NHF_REFORMED_BUTTONFUNCTIONS_H
