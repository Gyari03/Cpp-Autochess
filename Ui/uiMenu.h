/**
 * @file uiMenu.h
 * @brief uiMenu osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_UIMENU_H
#define NHF_REFORMED_UIMENU_H
#include "../Menu/menu.h"
#include "ui.h"

/**
 * @brief uiMenu osztály, ami a menü megjelenítéséért felelős.
 */
class uiMenu:public ui {
private:
    Menu* menu;         /**< A menü, amit meg szeretnénk jeleníteni */
public:
    uiMenu(Menu* menu,std::ostream& os,std::istream& is); /**< Konstruktor menüobjektummal paraméterként */
    ~uiMenu();          /**< Destruktor */

    /**
     * @brief A menü megjelenítőfüggvénye.
     * Kirajzolja a menüt a képernyőre.
     */
    void display() override;

    /**
     * @brief A menü inputkezelésével foglalkozó függvény.
     * A felhasználó által bevitt parancsokat értelmezi, és ezek alapján választ gombot a menüben.
     * @return true: sikeresen megnyomott gomb 
     * @return false:kilépés a függvényből, vagy hibás bemenet.
     */
    bool handleInput() override;

    /**
     * @brief A menü inaktív állapotát kezelő függvény.
     * Amikor a menü vár arra, hogy válasszunk egy gombot.
     */
    void idle() override;

    /**
     * @brief Ez az idle() annyiban különbözik az előzőtől, hogy ez megnézi a handleInput() visszatérési értékét, és ha helyesen futott le a függvény utána kilép majd a menüből.
     */
    void refreshingidle();

    /**
     * @brief Futtatja a paraméterként kapott menüt.
     * Létrehoz neki egy uiMenu objektumot és azt berakja idle() pozícióba.
     * @param menuPtr A menüre mutató pointer
     */
    static void Run(Menu* menu,std::ostream& os, std::istream& is);

    /**
     * @brief Futtatja a paraméterként kapott menüt.
     * Létrehoz neki egy uiMenu objektumot és azt berakja refreshingidle() pozícióba.
     * @param menuPtr A menüre mutató pointer
     */
    static void refreshingRun(Menu* menuPtr,std::ostream& os,std::istream& is);
};
#endif //NHF_REFORMED_UIMENU_H