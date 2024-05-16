#include <iostream>
#include <sstream>
#include "Menu/menu.h"
#include "Menu/button.h"
#include "Menu/buttonfunctions.h"
#include "Ui/ui.h"
#include "Ui/uiMenu.h"
#include "Ui/uiEditor.h"
#include "Ui/uiGame.h"
#include "Memtrace/gtest_lite.h"
#include "Memtrace/memtrace.h"
#include "Exception/Error.h"
#include "Menu/buttonfunctions.h"
#include "Editor/Editor.h"
#include "Game/Piece.h"

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
            menu.addButton(Button("Tesztgomb1",menu.getIdCounter(),&ButtonFunctions::Play,std::cout,std::cin));
            EXPECT_EQ(1,menu.getIdCounter());

            //getButton
            EXPECT_STREQ("Tesztgomb1",menu.getButton(0)->getName());

            //addButton
            menu.addButton(Button("Tesztgomb2",menu.getIdCounter(),&ButtonFunctions::Play,std::cout,std::cin));
            EXPECT_EQ(2,menu.getIdCounter());

            //incrementCounter
            menu.incrementCounter();
            EXPECT_EQ(3,menu.getIdCounter());
    } ENDM;

//Button
    TEST(Button, fuggvenyek){
     Army army1;
     Army army2;

     Button button1("Teszt1",1,&ButtonFunctions::Play,std::cout,std::cin);

     //Egyszerű menüt megnyitó gomb:
     EXPECT_STREQ("Teszt1",button1.getName());
     EXPECT_EQ(1,button1.getId());

    //1 army paraméterű gomb
     Button button2("Teszt2", 2, &ButtonFunctions::ChooseArmy, &army1,std::cout,std::cin);
     EXPECT_STREQ("Teszt2",button2.getName());
     EXPECT_EQ(2,button2.getId());

     //2 army paraméterű gomb
     Button button3("Teszt3", 3, &ButtonFunctions::PlayMatch, &army1, &army2,std::cout,std::cin);
     EXPECT_STREQ("Teszt3",button3.getName());
     EXPECT_EQ(3,button3.getId());

     //setId
     button3.setId(6);
     EXPECT_EQ(6,button3.getId());
    } ENDM;


    //Ennel létrehoztunk egy testing class-t a tesztelésekre
    TEST(ButtonFunctionHandler, fuggvenyek){
        std::stringstream os;
        ButtonFunctionHandler buttonFunctionHandler(&ButtonFunctions::tesztfuggveny,os,std::cin);
        buttonFunctionHandler.execute();
        EXPECT_STREQ("Lefutottam!",os.str().c_str()); //sikerült lefuttatnia a benne lévő függvényt
    } ENDM;


    TEST(ButtonFunctions, fuggvenyek){
        std::stringstream os;
        std::stringstream is;

        is<<0;
        ButtonFunctions::MainMenu(os,is);
        EXPECT_STREQ("1)Play\n0)Exit\n",os.str().c_str());

        is.clear();
        os.str("");

        is<<0;
        ButtonFunctions::Play(os,is);
        EXPECT_STREQ("1)New game\n2)Army editor\n",os.str().c_str());

        is.clear();
        os.str("");

        is<<0;
        ButtonFunctions::NewGame(os,is);
        EXPECT_STREQ("1)Team1\n2)Team2\n3)Play game\n",os.str().c_str());

        is.clear();
        os.str("");
    }ENDM;

    TEST(List, fuggvenyek){
        List<int> lista;
        List<int> lista2;

        EXPECT_EQ(0,lista.getSize());

        lista.addtoList(new int(4));
        lista.addtoList(new int(1008));
        lista.addtoList(new int(314));
        lista.addtoList(new int(271));

        EXPECT_EQ(4,*lista[0]);
        EXPECT_NE(271,*lista[2]);
        EXPECT_EQ(4,lista.getSize());

        lista.deletefromList(lista[2]);

        EXPECT_EQ(271,*lista[2]);
        EXPECT_EQ(3,lista.getSize());

        lista2.consumeList(lista);
        EXPECT_EQ(271,*lista2[2]);
        EXPECT_EQ(3,lista2.getSize());

        EXPECT_EQ(1008,*lista2.Maximum());

        Node<int> tesztnode(new int(928));
        EXPECT_EQ(928,*tesztnode.getData());

        EXPECT_EQ(0,lista.getSize());

    }ENDM;

    TEST(Editor,fuggvenyek){
        Editor editorteszt;

        EXPECT_EQ(false,editorteszt.getExit());
        EXPECT_EQ(false,editorteszt.getDelete());

        EXPECT_TRUE(editorteszt.searchFor(1, 1) == nullptr);
        EXPECT_EQ(editorteszt.getArmy()->getsizeofArmy(),0);

        editorteszt.updateExit();
        editorteszt.updateDelete();
        EXPECT_TRUE(editorteszt.getDelete());
        EXPECT_TRUE(editorteszt.getExit());

        Piece* newpiece = Piece::createPiece('K',1,1);
        editorteszt.getArmy()->addPiece(*newpiece);
        EXPECT_FALSE(editorteszt.searchFor(1, 1) == nullptr);

    }ENDM;

    TEST(uiMenu,fuggvenyek){
        std::stringstream os;
        std::stringstream is;

        Menu menu;
        menu.addButton(Button("New game", menu.getIdCounter(), &ButtonFunctions::NewGame,os,is));
        menu.addButton(Button("Army editor", menu.getIdCounter(), &ButtonFunctions::ArmyMenu,os,is));

        uiMenu ui(&menu,os,is);

        ui.display();
        EXPECT_STREQ("1)New game\n2)Army editor\n",os.str().c_str());

        is.clear();
        os.str("");

        EXPECT_FALSE(menu.getExit());

        is<<0;
        ui.handleInput();
        EXPECT_TRUE(menu.getExit());

        is.clear();
        os.str("");

        is<<100;
        EXPECT_THROW(ui.handleInput(),Error);

        is.clear();
        os.str("");

        is<<"Gabica";
        EXPECT_THROW(ui.handleInput(),Error);

        is.clear();
        os.str("");

        ui.idle(); //ki fog lépni egyből mert getExit()=true
        EXPECT_STREQ("",os.str().c_str()); //üreset kell hogy kapjon

        is.clear();
        os.str("");

        ui.refreshingidle(); //ki fog lépni egyből mert getExit()=true
        EXPECT_STREQ("",os.str().c_str()); //üreset kell hogy kapjon
        }ENDM;

    TEST(uiEditor,fuggvenyek){
        Editor editor;
        std::stringstream os;
        std::stringstream is;

        EXPECT_TRUE(editor.getArmy()->getPiece(1,1)==nullptr);

        uiEditor ui(&editor,os,is);

        is<<"K11";
        ui.handleInput();
        EXPECT_FALSE(editor.getArmy()->getPiece(1,1)==nullptr);

        is.clear();
        os.str("");

        is<<"M33"; //nem létező bábutípusra throw
        EXPECT_THROW(ui.handleInput(),Error);

        is.clear();
        os.str("");

        is<<"D11";
        ui.handleInput();
        EXPECT_TRUE(editor.getArmy()->getPiece(1,1)==nullptr);

        char urestabla[]="     1         2         3         4         5         6         7         8\n"
                     "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "#         #         #         #         #         #         #         #         #  4\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "#         #         #         #         #         #         #         #         #  3\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "#         #         #         #         #         #         #         #         #  2\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "#         #         #         #         #         #         #         #         #  1\n"
                     "#         #         #         #         #         #         #         #         #\n"
                     "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n";

        is.clear();
        os.str("");

        ui.display();
        EXPECT_STREQ(urestabla,os.str().c_str());

        is.clear();
        os.str("");

        is<<"Q22";
        ui.handleInput();
        editor.updateExit();


        ui.idle();

        char tablababuval[]="     1         2         3         4         5         6         7         8\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  4\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  3\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #    Q    #         #         #         #         #         #         #  2\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  1\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n";

        EXPECT_STREQ(tablababuval,os.str().c_str());
    }ENDM;

    TEST(uiGame,fuggvenyek){
        Army army1;
        Army army2;
        Game game(&army1,&army2);
        std::stringstream os;
        std::stringstream is;
        uiGame ui(&game,os,is);

        char urestabla[]="     1         2         3         4         5         6         7         8\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  8\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  7\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  6\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  5\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  4\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  3\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  2\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "#         #         #         #         #         #         #         #         #  1\n"
                         "#         #         #         #         #         #         #         #         #\n"
                         "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n";
        ui.display();
        EXPECT_STREQ(urestabla,os.str().c_str());

        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('K',1,1));


        char tablababuval[]="     1         2         3         4         5         6         7         8\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  8\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  7\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  6\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  5\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  4\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  3\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#         #         #         #         #         #         #         #         #  2\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "#    K    #         #         #         #         #         #         #         #  1\n"
                            "#         #         #         #         #         #         #         #         #\n"
                            "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n";

            is.clear();
            os.str("");

            ui.renderTable();
            EXPECT_STREQ(tablababuval,os.str().c_str());

            is.clear();
            os.str("");

            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('K',5,8));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q',1,8));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q',2,8));
            //checkifover;

            is.clear();
            os.str("");

            ui.handleInput(); //fehér jön       //handleinput a playroundot hívja meg így is
            game.playRound(); //fekete jön-> le is üti a fehér királyt
            game.playRound(); //fehér próbál jönni, de nincs mivel->veszt


            ui.idle();
            EXPECT_STREQ("Team 2 Wins!",os.str().c_str());

            is.clear();
            os.str("");

            ui.endScreen();
            EXPECT_STREQ("Team 2 Wins!",os.str().c_str());
        }ENDM;

    TEST(uiGame,run_fuggveny){
        Army army1;
        Army army2;
        Game game(&army1,&army2);
        std::stringstream os;
        std::stringstream is;
        uiGame ui(&game,os,is);

        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('K',1,1));
        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q',1,2));
        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q',2,1));

        game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('K',8,8));

        uiGame::Run(&game,os,is);

        int siz = strlen("Team 1 Wins!");
        std::string osstring = os.str();
        std::string endscreen = osstring.substr(osstring.size() - siz);
        EXPECT_STREQ("Team 1 Wins!",endscreen.c_str());
        //Feltételezve azt, hogy team 1 nyer, mivel a team 2-nek a nyerés majdnem lehetetlen.
    }ENDM;

    TEST(Error,fuggvenyek){
        std::stringstream os;

        try{
            throw Error("Test");
        }catch (const std::exception &e) {os << "Error:" << e.what() << std::endl;}

        EXPECT_STREQ("Error:Test\n",os.str().c_str());
        EXPECT_THROW(throw Error("Test"),Error);
    }ENDM;

    TEST(Piece,fuggvenyek){
        Piece* piece1 = Piece::createPiece('K',5,6);
        EXPECT_EQ(5,piece1->getCoordX());
        EXPECT_EQ(6,piece1->getCoordY());
        EXPECT_EQ('K',piece1->getName());

        piece1->setCoordX(2);
        piece1->setCoordY(8);
        EXPECT_EQ(2,piece1->getCoordX());
        EXPECT_EQ(8,piece1->getCoordY());




        delete piece1;
    }ENDM;



    char a;std::cin>>a;
#endif
}