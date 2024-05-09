#ifndef NHF_REFORMED_BUTTONFUNCTIONS_H
#define NHF_REFORMED_BUTTONFUNCTIONS_H
#include "../Game/Army.h"

Menu* MainMenu();

void Play();

void Exit();

void NewGame();

void ArmyMenu();

void CreateArmy();

void EditArmy(Army*);

void ChooseArmy(Army*); //a paraméterként megkapott-ba tölti majd be az armyt

void Gamesz(Army* reg1, Army* reg2);

#endif //NHF_REFORMED_BUTTONFUNCTIONS_H
