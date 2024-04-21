#include "ButtonFunction.h"

void ButtonFunction::execute() {
    if(function!=nullptr){function();return;}
    else if(functionArmy!=nullptr){functionArmy(armyPointer);return;}//mégis át kéne adni az armyt
}
