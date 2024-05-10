#include <iostream>
#include "Menu/menu.h"
#include "Menu/button.h"
#include "Menu/buttonfunctions.h"
#include "Ui/ui.h"
#include "Ui/uiMenu.h"
//#include "Memtrace/gtest_lite.h"
#include "Memtrace/memtrace.h"

//#define CPORTA

int main() {
    std::srand(std::time(nullptr)); //random seed beállítása
#ifndef CPORTA
    ButtonFunctions::MainMenu();
#else
    //tesztek
#endif
    return 0;

}