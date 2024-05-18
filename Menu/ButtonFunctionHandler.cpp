#include "ButtonFunctionHandler.h"

#include "../Memtrace/memtrace.h"

void ButtonFunctionHandler::execute() {
    if(fun != nullptr){fun(*os,*is);return;}
    else if(funArmy != nullptr){funArmy(regArmy1,*os,*is);return;}
    else if(funArmyFor2 != nullptr){funArmyFor2(regArmy1, regArmy2,*os,*is);return;}
}
