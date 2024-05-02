#include "ButtonFunction.h"

void ButtonFunction::execute() {
    if(fun != nullptr){fun();return;}
    else if(funArmy != nullptr){funArmy(regArmy1);return;}//mégis át kéne adni az armyt
    else if(funArmyFor2 != nullptr){funArmyFor2(regArmy1, regArmy2);return;}
}
