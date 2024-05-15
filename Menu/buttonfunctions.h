/**
 * @file buttonfunctions.h
 * @brief Ez a header tartalmazza a függvénypointereket, amik aktiválódnak amikor egy gombot nyomunk le egy menüben.
 */

#ifndef NHF_REFORMED_BUTTONFUNCTIONS_H
#define NHF_REFORMED_BUTTONFUNCTIONS_H
#include "../Game/Army.h"


/**
 * @brief Függvénypointerek, amik aktiválódnak ha lenyomják az őket tartalmazó gombot.
 */
class ButtonFunctions{
public:
    static void MainMenu();     /**<Főmenü függvény*/

    /**
     * @brief Ebben a menüben kell választani aközött, hogy szerkeszteni vagy játszani szeretnénk
     * Működése:
     * - Létrejön egy Menu objektum.
     * - Hozzáadódnak a szükséges gombok, a neveikkel funkcióikkal.
     * - Futtatja a Menüt->választ a felhaszáló a gombok közül.
     */
    static void Play();

    /**
     * @brief Menü a játék futtatása előtt.
     * @details Van benne 2 db army amikbe áttudja tölteni a felhasználó a fájlból a kiválasztott seregeit.
     * Majd azokat a seregeket adja át paraméterként a játék futtatásánál.
     */
    static void NewGame();      

    /**
     * @brief Létrehoz egy menüt ami kimutatja az összes sereget ami le van mentve.
     * Használt ez arra, hogy az editornál kiválasszunk egy sereget editelésre
     * */
    static void ArmyMenu();    

    /**
     * @brief Megnyit egy editor-t paraméternélküli konstruktorral, ezzel új sereget lehet létrehozni.
     */
    static void CreateArmy();

    /**
     * @brief Sereg szerkesztésére használt fv.
     */
    static void EditArmy(Army*);

    /**
     * @brief Sereg kiválasztására használt fv.
     * A sereg amit kiválaszt az armies.dat-ből kiválasztott listából, azt tölti majd át a paraméterként kapott army*-be.
     */
    static void ChooseArmy(Army*); //a paraméterként megkapott paraméter-be tölti majd be az armyt amit választ
    
    /**
     * @brief Ez indítja el a játékot
     * @param reg1 Fehér csapat
     * @param reg2 Fekete csapat
     */
    static void PlayMatch(Army* reg1, Army* reg2);


    //Teszteknél felhasznált függvény
    static void tesztfuggveny(std::ostream& os);
};
#endif //NHF_REFORMED_BUTTONFUNCTIONS_H