#include <iostream>
#include "Menu/menu.h"
#include "Menu/button.h"
#include "Menu/buttonfunctions.h"
#include "Ui/ui.h"
#include "Ui/uiMenu.h"
//#include "Memtrace/gtest_lite.h"
#include "Memtrace/memtrace.h"
#include "Exception/Error.h"

//#define CPORTA

int main() {
    std::srand(std::time(nullptr)); //random seed beállítása
#ifndef CPORTA
    ButtonFunctions::MainMenu();

   /* try{
        int a = 3;
        if (a > 2) // EZ ROSSZ ÁLLÍTSUK MEG SOROST
            throw Error("Katica");
    }
    catch (std::exception& e){
        std::cout << e.what();
    }*/

#else
    //tesztek
#endif
    return 0;

}