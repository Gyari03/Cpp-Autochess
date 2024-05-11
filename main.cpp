#include <iostream>
#include "Menu/menu.h"
#include "Menu/button.h"
#include "Menu/buttonfunctions.h"
#include "Ui/ui.h"
#include "Ui/uiMenu.h"
#include "Memtrace/gtest_lite.h"
#include "Memtrace/memtrace.h"
#include "Exception/Error.h"
#include "Menu/buttonfunctions.h"

#define CPORTA

int main() {
#ifndef CPORTA
    std::srand(std::time(nullptr)); //random seed beállítása
    ButtonFunctions::MainMenu();
#else

//Menu
    TEST(Menu, fuggvenyek){
            Menu menu;

            //default ctor
            EXPECT_EQ(0,menu.getIdCounter());
            EXPECT_FALSE(menu.getExit());

            //updateExit - getExit
            menu.updateExit();
            EXPECT_TRUE(menu.getExit());

            //getIdCounter
            menu.addButton(Button("Tesztgomb1",menu.getIdCounter(),&ButtonFunctions::Play));
            EXPECT_EQ(1,menu.getIdCounter());

            //getButton
            EXPECT_STREQ("Tesztgomb1",menu.getButton(0)->getName());

            //addButton
            menu.addButton(Button("Tesztgomb2",menu.getIdCounter(),&ButtonFunctions::Play));
            EXPECT_EQ(2,menu.getIdCounter());

            //incrementCounter
            menu.incrementCounter();
            EXPECT_EQ(3,menu.getIdCounter());
    } ENDM;

//Button
    TEST(Button, fuggvenyek){
     Army army1;
     Army army2;

     Button button1("Teszt1",1,&ButtonFunctions::Play);

     //Egyszerű menüt megnyitó gomb:
     EXPECT_STREQ("Teszt1",button1.getName());
     EXPECT_EQ(1,button1.getId());

    //1 army paraméterű gomb
     Button button2("Teszt2", 2, &ButtonFunctions::ChooseArmy, &army1);
     EXPECT_STREQ("Teszt2",button2.getName());
     EXPECT_EQ(2,button2.getId());

     //2 army paraméterű gomb
     Button button3("Teszt3", 3, &ButtonFunctions::PlayMatch, &army1, &army2);
     EXPECT_STREQ("Teszt3",button3.getName());
     EXPECT_EQ(3,button3.getId());
    } ENDM;
#endif
}