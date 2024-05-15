/**
 * @file uiGame.h
 * @brief uiGame osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_UIGAME_H
#define NHF_REFORMED_UIGAME_H
#include "ui.h"
#include "../Game/Game.h"
#include <iostream>

/**
 * @brief uiGame osztály, ami a játék megjelenítéséért felelős.
 */
class uiGame:public ui {
private:
    Game* game;         /**< A játék, amit meg szeretnénk jeleníteni */
public:
    uiGame(Game* game,std::ostream& os,std::istream& is);     /**< Konstruktor játékobjektummal paraméterként */
    ~uiGame();                                                /**< Destruktor */

    /**
     * @brief A játék megjelenítőfüggvénye.
     * Tartalmaz két alfüggvényt:
     * - clearScreen() : letisztítja az előző táblát a képernyőről
     * - renderTable() : visszarajzolja a táblát, de már az új állapotában.
     */
    void display() override;

    /**
     * @brief A játék inputkezelésével foglalkozó függvény.
     * - A felhasználó által bevitt parancsokat értelmezi, és ezek alapján módosítja a játék állapotát.
     * - Lekezeli a játék befejezését is, ha a játék véget ér, akkor átirányít a végeképernyőre.
     */
    bool handleInput() override;

    /**
     * @brief A játéktábla lerendereléséért felelős függvény.
     * Ez már a teljes 8X8-as táblát meg fogja jeleníteni mindkét csapattal rajta.
     */
    void renderTable();

    /**
     * @brief A játék inaktív állapotát kezelő függvény.
     * Amikor a 2 irányú kommunikáció megy(Itt például a uiGame-ban nincsen felhasználói input, a gép magának adja az inputokat és arra válaszol a megjelenítéssel)
     */
    void idle() override;

    /**
     * @brief A játék végét jelző képernyőt megjelenítő függvény.
     * Kiírja a játék végén megjelenő üzenetet a képernyőre.(Döntetlen,Csapat1 nyert, Csapat2 nyert)
     */
    void endScreen();

    /**
     * @brief Futtatja a paraméterként kapott játékot.
     * Létrehoz neki egy uiGame objektumot és azt berakja idle() pozícióba.
     * @param gameptr A játékra mutató pointer
     */
    static void Run(Game* gameptr,std::ostream& os,std::istream& is);
};
#endif //NHF_REFORMED_UIGAME_H