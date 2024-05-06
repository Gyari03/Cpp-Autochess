#include <iostream>
#include "Menu/menu.h"
#include "Menu/button.h"
#include "Menu/buttonfunctions.h"
#include "Ui/ui.h"
#include "Ui/uiMenu.h"
#include "Memtrace/gtest_lite.h"
#include "Memtrace/memtrace.h"

//#define CPORTA

#ifndef CPORTA
int main() {
    Run(MainMenu());
}
#endif

#ifdef CPORTA
int main(){
    //tesztek
}

#endif