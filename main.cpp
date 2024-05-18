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
#include "File Management/Filemanagement.h"

//#define CPORTA

int main() {
#ifndef CPORTA
    std::srand(std::time(nullptr)); //random seed beállítása
    ButtonFunctions::MainMenu();
#else

//Menu
    TEST(Menu, fuggvenyek)
        {
            Menu menu;

            //default ctor
            EXPECT_EQ(0, menu.getIdCounter());
            EXPECT_FALSE(menu.getExit());

            //updateExit - getExit
            menu.updateExit();
            EXPECT_TRUE(menu.getExit());

            //getIdCounter
            menu.addButton(Button("Tesztgomb1", menu.getIdCounter(), &ButtonFunctions::Play, std::cout, std::cin));
            EXPECT_EQ(1, menu.getIdCounter());

            //getButton
            EXPECT_STREQ("Tesztgomb1", menu.getButton(0)->getName());

            //addButton
            menu.addButton(Button("Tesztgomb2", menu.getIdCounter(), &ButtonFunctions::Play, std::cout, std::cin));
            EXPECT_EQ(2, menu.getIdCounter());

            //incrementCounter
            menu.incrementCounter();
            EXPECT_EQ(3, menu.getIdCounter());
        }ENDM;

//Button
    TEST(Button, fuggvenyek)
        {
            Army army1;
            Army army2;

            Button button1("Teszt1", 1, &ButtonFunctions::Play, std::cout, std::cin);

            //Egyszerű menüt megnyitó gomb:
            EXPECT_STREQ("Teszt1", button1.getName());
            EXPECT_EQ(1, button1.getId());

            //1 army paraméterű gomb
            Button button2("Teszt2", 2, &ButtonFunctions::ChooseArmy, &army1, std::cout, std::cin);
            EXPECT_STREQ("Teszt2", button2.getName());
            EXPECT_EQ(2, button2.getId());

            //2 army paraméterű gomb
            Button button3("Teszt3", 3, &ButtonFunctions::PlayMatch, &army1, &army2, std::cout, std::cin);
            EXPECT_STREQ("Teszt3", button3.getName());
            EXPECT_EQ(3, button3.getId());

            //setId
            button3.setId(6);
            EXPECT_EQ(6, button3.getId());
        }ENDM;


    //Ennel létrehoztunk egy testing class-t a tesztelésekre
    TEST(ButtonFunctionHandler, fuggvenyek)
        {
            std::stringstream os;
            ButtonFunctionHandler buttonFunctionHandler(&ButtonFunctions::tesztfuggveny, os, std::cin);
            buttonFunctionHandler.execute();
            EXPECT_STREQ("Lefutottam!", os.str().c_str()); //sikerült lefuttatnia a benne lévő függvényt
        }ENDM;


    TEST(ButtonFunctions, fuggvenyek)
        {
            std::stringstream os;
            std::stringstream is;

            is << 0;
            ButtonFunctions::MainMenu(os, is);
            EXPECT_STREQ("1)Play\n0)Exit\n", os.str().c_str());

            is.clear();
            os.str("");

            is << 0;
            ButtonFunctions::Play(os, is);
            EXPECT_STREQ("1)New game\n2)Army editor\n", os.str().c_str());

            is.clear();
            os.str("");

            is << 0;
            ButtonFunctions::NewGame(os, is);
            EXPECT_STREQ("1)Team1\n2)Team2\n3)Play game\n", os.str().c_str());

            is.clear();
            os.str("");
        }ENDM;

    TEST(List, fuggvenyek)
        {
            List<int> lista;
            List<int> lista2;

            EXPECT_EQ(0, lista.getSize());

            lista.addtoList(new int(4));
            lista.addtoList(new int(1008));
            lista.addtoList(new int(314));
            lista.addtoList(new int(271));

            EXPECT_EQ(4, *lista[0]);
            EXPECT_NE(271, *lista[2]);
            EXPECT_EQ(4, lista.getSize());

            lista.deletefromList(lista[2]);

            EXPECT_EQ(271, *lista[2]);
            EXPECT_EQ(3, lista.getSize());

            lista2.consumeList(lista);
            EXPECT_EQ(271, *lista2[2]);
            EXPECT_EQ(3, lista2.getSize());

            EXPECT_EQ(1008, *lista2.Maximum());

            Node<int> tesztnode(new int(928));
            EXPECT_EQ(928, *tesztnode.getData());

            EXPECT_EQ(0, lista.getSize());

        }ENDM;

    TEST(Editor, fuggvenyek)
        {
            Editor editorteszt;

            EXPECT_EQ(false, editorteszt.getExit());
            EXPECT_EQ(false, editorteszt.getDelete());

            EXPECT_TRUE(editorteszt.searchFor(1, 1) == nullptr);
            EXPECT_EQ(editorteszt.getArmy()->getsizeofArmy(), 0);

            editorteszt.updateExit();
            editorteszt.updateDelete();
            EXPECT_TRUE(editorteszt.getDelete());
            EXPECT_TRUE(editorteszt.getExit());

            Piece *newpiece = Piece::createPiece('K', 1, 1);
            editorteszt.getArmy()->addPiece(*newpiece);
            EXPECT_FALSE(editorteszt.searchFor(1, 1) == nullptr);

        }ENDM;

    TEST(uiMenu, fuggvenyek)
        {
            std::stringstream os;
            std::stringstream is;

            Menu menu;
            menu.addButton(Button("New game", menu.getIdCounter(), &ButtonFunctions::NewGame, os, is));
            menu.addButton(Button("Army editor", menu.getIdCounter(), &ButtonFunctions::ArmyMenu, os, is));

            uiMenu ui(&menu, os, is);

            ui.display();
            EXPECT_STREQ("1)New game\n2)Army editor\n", os.str().c_str());

            is.clear();
            os.str("");

            EXPECT_FALSE(menu.getExit());

            is << "0";
            ui.handleInput();
            EXPECT_TRUE(menu.getExit());

            is.clear();
            os.str("");

            is << 100;
            EXPECT_THROW(ui.handleInput(), Error);

            is.clear();
            os.str("");

            is << "Gabica";
            EXPECT_THROW(ui.handleInput(), Error);

            is.clear();
            os.str("");

            ui.idle(); //ki fog lépni egyből mert getExit()=true
            EXPECT_STREQ("", os.str().c_str()); //üreset kell hogy kapjon

            is.clear();
            os.str("");

            ui.refreshingidle(); //ki fog lépni egyből mert getExit()=true
            EXPECT_STREQ("", os.str().c_str()); //üreset kell hogy kapjon
        }ENDM;

    TEST(uiEditor, fuggvenyek)
        {
            Editor editor;
            std::stringstream os;
            std::stringstream is;

            EXPECT_TRUE(editor.getArmy()->getPiece(1, 1) == nullptr);

            uiEditor ui(&editor, os, is);

            is << "K11";
            ui.handleInput();
            EXPECT_FALSE(editor.getArmy()->getPiece(1, 1) == nullptr);

            is.clear();
            os.str("");

            is << "M33"; //nem létező bábutípusra throw
            EXPECT_THROW(ui.handleInput(), Error);

            is.clear();
            os.str("");

            is << "D11";
            ui.handleInput();
            EXPECT_TRUE(editor.getArmy()->getPiece(1, 1) == nullptr);

            char urestabla[] = "     1         2         3         4         5         6         7         8\n"
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
            EXPECT_STREQ(urestabla, os.str().c_str());

            is.clear();
            os.str("");

            is << "Q22";
            ui.handleInput();
            editor.updateExit();


            ui.idle();

            char tablababuval[] = "     1         2         3         4         5         6         7         8\n"
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

            EXPECT_STREQ(tablababuval, os.str().c_str());
        }ENDM;

    TEST(uiGame, fuggvenyek)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;
            uiGame ui(&game, os, is);

            char urestabla[] = "     1         2         3         4         5         6         7         8\n"
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
            EXPECT_STREQ(urestabla, os.str().c_str());

            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('K', 1, 1));


            char tablababuval[] = "     1         2         3         4         5         6         7         8\n"
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
            EXPECT_STREQ(tablababuval, os.str().c_str());

            is.clear();
            os.str("");

            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('K', 5, 8));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q', 1, 8));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q', 2, 8));
            //checkifover;

            is.clear();
            os.str("");

            ui.handleInput(); //fehér jön       //handleinput a playroundot hívja meg így is
            game.playRound(); //fekete jön-> le is üti a fehér királyt
            game.playRound(); //fehér próbál jönni, de nincs mivel->veszt


            ui.idle();
            EXPECT_STREQ("Team 2 Wins!", os.str().c_str());

            is.clear();
            os.str("");

            ui.endScreen();
            EXPECT_STREQ("Team 2 Wins!", os.str().c_str());
        }ENDM;

    TEST(uiGame, run_fuggveny)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;
            uiGame ui(&game, os, is);

            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('K', 1, 1));
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q', 1, 2));
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q', 2, 1));

            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('K', 8, 8));

            uiGame::Run(&game, os, is);

            //int siz = strlen("Team 1 Wins!");
            std::string osstring = os.str();
            std::string endscreen = osstring.substr(osstring.size() - 12);
            EXPECT_STREQ("Team 1 Wins!", endscreen.c_str());
            //Feltételezve azt, hogy team 1 nyer, mivel a team 2-nek a nyerés majdnem(kicsi esélye azért van hogy hibázzon a teszt) lehetetlen.
        }ENDM;

    TEST(Error, fuggvenyek)
        {
            std::stringstream os;

            try {
                throw Error("Test");
            } catch (const std::exception &e) { os << "Error:" << e.what() << std::endl; }

            EXPECT_STREQ("Error:Test\n", os.str().c_str());
            EXPECT_THROW(throw Error("Test"), Error);
        }ENDM;

    TEST(Piece, fuggvenyek)
        {
            Piece *piece1 = Piece::createPiece('K', 5, 6);
            EXPECT_EQ(5, piece1->getCoordX());
            EXPECT_EQ(6, piece1->getCoordY());
            EXPECT_EQ('K', piece1->getName());

            piece1->setCoordX(2);
            piece1->setCoordY(8);
            EXPECT_EQ(2, piece1->getCoordX());
            EXPECT_EQ(8, piece1->getCoordY());
            delete piece1;
        }ENDM;

    TEST(Piece, lepesfuggvenyek)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;

            //Tesztelésre felhasznált bábu létrehozása
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('P', 2, 4));

            //Upwards fv.
            Piece::upwards(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            bool current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 2 && y == 6) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //Downwards fv.
            Piece::downwards(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 2 && y == 2) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //Rightwards fv.
            Piece::rightwards(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 6 && y == 4) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //Leftwards fv.
            Piece::leftwards(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 1 && y == 4) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //Orthogonal fv.
            Piece::orthogonal(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 8 && y == 8) {
                    current = true;
                    break;
                }
            }
            EXPECT_FALSE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //diagonalUpRight
            Piece::diagonalUpRight(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 4 && y == 6) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //diagonalUpLeft
            Piece::diagonalUpLeft(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 1 && y == 5) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //diagonalDownRight
            Piece::diagonalDownRight(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 4 && y == 2) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //diagonalDownLeft
            Piece::diagonalDownLeft(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 1 && y == 3) {
                    current = true;
                    break;
                }
            }
            EXPECT_TRUE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //diagonal
            Piece::diagonal(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 2 && y == 6) {
                    current = true;
                    break;
                }
            }
            EXPECT_FALSE(current);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();

            //pawnMove
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q', 3, 5)); //leüthető bábu létrehozása

            Piece::pawnMove(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            bool canDestroyOtherPiece = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 2 && y == 5) { current = true; }
                if (x == 3 && y == 5) { canDestroyOtherPiece = true; }
            }
            EXPECT_TRUE(current && canDestroyOtherPiece);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();
            game.getTeam(1)->getArmy()->deletePiece(3, 5);

            //horseMove
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q', 3, 6)); //leüthető bábu létrehozása
            Piece::horseMove(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            canDestroyOtherPiece = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 1 && y == 2) { current = true; }
                if (x == 3 && y == 6) { canDestroyOtherPiece = true; }
            }
            EXPECT_TRUE(current && canDestroyOtherPiece);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();
            game.getTeam(1)->getArmy()->deletePiece(3, 6);

            //kingMove
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q', 3, 3)); //leüthető bábu létrehozása
            Piece::kingMove(game.getTeam(0)->getArmy()->getPiece(2, 4), &game);
            current = false;
            canDestroyOtherPiece = false;
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves()[i]->getCoordY();
                if (x == 1 && y == 5) { current = true; }
                if (x == 3 && y == 3) { canDestroyOtherPiece = true; }
            }
            EXPECT_TRUE(current && canDestroyOtherPiece);
            game.getTeam(0)->getArmy()->getPiece(2, 4)->getMoves().clear();
            game.getTeam(1)->getArmy()->deletePiece(3, 3);

        }ENDM;

    TEST(Bishop, fuggvenyek)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;

            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('B', 4, 5));

            //szövetséges létrehozása:rajta nem léphet túl és nem ütheti le
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q', 3, 6));
            bool doesNotDestroyAlly = true;
            bool doesNotJumpThroughAlly = true;
            //ellenség létrehozása
            bool destroysEnemy = false;
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('H', 7, 8));

            game.getTeam(0)->getArmy()->getPiece(4, 5)->calculateMoves(&game);
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordY();
                if (x == 3 && y == 6) { doesNotDestroyAlly = false; }
                if (x == 7 && y == 8) { destroysEnemy = true; }
                if (x == 2 && y == 7) { doesNotJumpThroughAlly = false; }
            }
            EXPECT_TRUE(doesNotDestroyAlly);
            EXPECT_TRUE(destroysEnemy);
            EXPECT_TRUE(doesNotJumpThroughAlly);
        }ENDM;

    TEST(Horse, fuggvenyek)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;

            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('H', 4, 5));

            //Szövetséges és ellenséges bábu
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q', 3, 3));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('Q', 5, 7));


            bool doesNotDestroyAlly = true;
            bool destroysEnemy = false;

            game.getTeam(0)->getArmy()->getPiece(4, 5)->calculateMoves(&game);
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordY();
                if (x == 3 && y == 3) { doesNotDestroyAlly = false; }
                if (x == 5 && y == 7) { destroysEnemy = true; }
            }

            EXPECT_TRUE(doesNotDestroyAlly);
            EXPECT_TRUE(destroysEnemy);
        }ENDM;

    TEST(Rook, fuggvenyek)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;

            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('R', 4, 5));

            //szövetséges és ellenséges bábu
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('P', 4, 3));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('K', 1, 5));


            bool doesNotDestroyAlly = true;
            bool destroysEnemy = false;

            game.getTeam(0)->getArmy()->getPiece(4, 5)->calculateMoves(&game);
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordY();
                if (x == 4 && y == 3) { doesNotDestroyAlly = false; }
                if (x == 1 && y == 5) { destroysEnemy = true; }
            }

            EXPECT_TRUE(doesNotDestroyAlly);
            EXPECT_TRUE(destroysEnemy);
        }ENDM;

    TEST(Queen, fuggvenyek)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;

            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q', 4, 5));

            //szövetséges és ellenséges bábu
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('P', 4, 3));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('B', 1, 8));

            bool doesNotDestroyAlly = true;
            bool destroysEnemy = false;

            game.getTeam(0)->getArmy()->getPiece(4, 5)->calculateMoves(&game);
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordY();
                if (x == 4 && y == 3) { doesNotDestroyAlly = false; }
                if (x == 1 && y == 8) { destroysEnemy = true; }
            }

            EXPECT_TRUE(doesNotDestroyAlly);
            EXPECT_TRUE(destroysEnemy);
        }ENDM;

    TEST(King, fuggvenyek)
        {
            Army army1;
            Army army2;
            Game game(&army1, &army2);
            std::stringstream os;
            std::stringstream is;

            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('K', 4, 5));

            //szövetséges és ellenséges bábu
            game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q', 3, 4));
            game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('P',5 , 5));

            bool doesNotDestroyAlly = true;
            bool destroysEnemy = false;

            game.getTeam(0)->getArmy()->getPiece(4, 5)->calculateMoves(&game);
            for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves().getSize(); i++) {
                int x = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordX();
                int y = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordY();
                if (x == 3 && y == 4) { doesNotDestroyAlly = false; }
                if (x == 5 && y == 5) { destroysEnemy = true; }
            }

            EXPECT_TRUE(doesNotDestroyAlly);
            EXPECT_TRUE(destroysEnemy);
        }ENDM;

    TEST(Pawn, fuggvenyek)
    {
        Army army1;
        Army army2;
        Game game(&army1, &army2);
        std::stringstream os;
        std::stringstream is;

        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('P', 4, 5));

        //szövetséges és ellenséges bábu
        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('Q', 3, 6));
        game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('P',5 , 6));

        bool doesNotDestroyAlly = true;
        bool destroysEnemy = false;

        game.getTeam(0)->getArmy()->getPiece(4, 5)->calculateMoves(&game);
        for (int i = 0; i < game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves().getSize(); i++) {
            int x = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordX();
            int y = game.getTeam(0)->getArmy()->getPiece(4, 5)->getMoves()[i]->getCoordY();
            if (x == 3 && y == 6) { doesNotDestroyAlly = false; }
            if (x == 5 && y == 6) { destroysEnemy = true; }
        }

        EXPECT_TRUE(doesNotDestroyAlly);
        EXPECT_TRUE(destroysEnemy);
    }ENDM;

    TEST(Army,fuggvenyek)
    {
        Army testarmy1;
        testarmy1.addPiece(*Piece::createPiece('P', 4, 5));

        EXPECT_TRUE(testarmy1.getPiece(0) != nullptr);

        testarmy1.setnameofArmy("Tesztarmy");

        EXPECT_STREQ("Tesztarmy", testarmy1.getnameofArmy());

        EXPECT_EQ(1, testarmy1.getsizeofArmy());

        testarmy1.incrementsizeofArmy();
        EXPECT_EQ(2, testarmy1.getsizeofArmy());

        testarmy1.setsizeofArmy(1);
        EXPECT_EQ(1, testarmy1.getsizeofArmy());

        testarmy1.deletePiece(4, 5);
        EXPECT_EQ(0, testarmy1.getsizeofArmy());

        Piece* piece = Piece::createPiece('K', 3, 3);
        testarmy1.addPiece(*piece);
        EXPECT_TRUE(testarmy1.partOfArmy(piece));

        testarmy1.addPiece(*Piece::createPiece('P', 4, 5));

        Army testarmy2;

        Army::copyArmy(&testarmy1,&testarmy2);
        EXPECT_TRUE(testarmy2.getPiece(0)->getCoordY()==3);
        EXPECT_STREQ("Tesztarmy", testarmy2.getnameofArmy());
        Army::mirrorArmy(&testarmy2);
        EXPECT_TRUE(testarmy2.getPiece(0)->getCoordY()==9-3);
    }ENDM;

    TEST(Computer,fuggvenyek)
    {
        Computer computer;
        Army army1;
        Army army2;
        Game game(&army1, &army2);

        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('R', 4, 5));
        game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('K', 4, 2));
        computer.calculateMoves(&game);

        bool foundCoordinate = false;
        bool bestMoveDecided = false;

        for (int i = 0; i < game.getTeam(0)->getTeamMoves().getSize(); i++) {
            int x = game.getTeam(0)->getTeamMoves()[i]->getCoordX();
            int y = game.getTeam(0)->getTeamMoves()[i]->getCoordY();
            if (x == 4 && y == 7) { foundCoordinate = true; }
        }
        EXPECT_TRUE(foundCoordinate);

        Move* chosen = computer.decideMove(&game);
        int chosen_x = chosen->getCoordX();
        int chosen_y = chosen->getCoordY();
        bestMoveDecided= chosen_x==4 && chosen_y==2;
        EXPECT_TRUE(bestMoveDecided);
    }ENDM;

    TEST(Game,fuggvenyek)
    {
        Army army1;
        Army army2;
        Game game(&army1, &army2);

        EXPECT_TRUE(game.isWhiteTurn());
        EXPECT_FALSE(game.getEnd());
        EXPECT_EQ(GameResult::DRAW,game.getResult());
        game.updateEnd();
        EXPECT_TRUE(game.getEnd());
        game.updateEnd();

        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('K', 1, 1));
        game.getTeam(1)->getArmy()->addPiece(*Piece::createPiece('K', 8, 8));
        game.getTeam(0)->getArmy()->addPiece(*Piece::createPiece('R', 4, 5));
        EXPECT_TRUE(game.searchFor(4,5)!=nullptr);
        EXPECT_EQ(TeamColor::White,game.getColorOfPiece(game.searchFor(4,5)));
        EXPECT_TRUE(game.occupied(4,5));

        game.playRound();
        EXPECT_FALSE(game.isWhiteTurn());

    }ENDM;

    TEST(Move,fuggvenyek)
    {
        Piece* origin = Piece::createPiece('Q',4,5);
        Move move1(origin,7,5,'K');
        Move move2(origin,4,7,'0');
        EXPECT_EQ(origin,move1.getPiece());
        EXPECT_EQ(7,move1.getCoordX());
        EXPECT_EQ(5,move1.getCoordY());
        EXPECT_EQ(0,move2.getWeight());
        EXPECT_TRUE(move1>move2);

        delete origin;
    }ENDM;

    TEST(Team,fuggvenyek)
    {
        Army army;
        Team team(&army,White);

        EXPECT_EQ(0,team.countAmountOfKigns());
        team.getArmy()->addPiece(*Piece::createPiece('K',4,5));
        EXPECT_EQ(1,team.countAmountOfKigns());
    }ENDM;

    TEST(Filemanagement,fuggvenyek)
    {
        std::string tesztseregnev = "Sereg1008";
        List<Army> lista1 = Filemanagement::ListofArmies("armies.dat");
        for(int i=0;i<lista1.getSize();i++){
            if(lista1[i]->getnameofArmy()==tesztseregnev){
                Filemanagement::DeleteArmy(lista1[i],"armies.dat");
            }
        }

        bool letezik = false;
        List<Army> lista3 = Filemanagement::ListofArmies("armies.dat");//megnézni, hogy tényleg nem létezik
        for(int i=0;i<lista3.getSize();i++){
            if(lista3[i]->getnameofArmy()==tesztseregnev){
                letezik = true;
            }
        }
        EXPECT_FALSE(letezik);

        Army newarmy;
        newarmy.addPiece(*Piece::createPiece('K',1,1));
        newarmy.setnameofArmy("Sereg1008");
        Filemanagement::AppendArmy(&newarmy,"armies.dat");


        List<Army> lista2 = Filemanagement::ListofArmies("armies.dat");
        for(int i=0;i<lista2.getSize();i++){
            if(lista2[i]->getnameofArmy()==tesztseregnev){
                letezik = true;
            }
        }
        EXPECT_TRUE(letezik);


    }ENDM;
#endif
}