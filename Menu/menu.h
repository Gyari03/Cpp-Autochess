/**
 * @file menu.h
 * @brief Ez a header tartalmazza a Menu osztályt, aminek köszönhetően lehet bejárni a programot.
 */

#ifndef NHF_REFORMED_MENU_H
#define NHF_REFORMED_MENU_H
#include "button.h"
#include <iostream>
#include <cstddef>


/**
 * @brief 
 * 
 */
class Menu{
private:
    size_t idCounter;       /**<Ezt az id-t osztja ki a gomboknak amikor létrejönnek. Emellet nagyon jó arra is, hogy kövessük vele a menü méretét.  */
    Button* buttonArray;    /**<Itt tárolódnak el a gombok  */
    bool exitRequested;     /**<Bool értéke arra, hogy a felhasználó ki szeretne-e lépni a menüből.  */
public:
    /**
     * @brief Default konstruktor
     */
    Menu();

    /**
     * @brief Menu destruktor
     * Törli a dinamikusan foglalt gombtömböt.
     */
    ~Menu();

    /**
     * @brief Inkrementálja az idCounter-t.
     */
    void incrementCounter();

    /**
     * @brief Igazzá teszi az exitRequested bool-t és akkor kilép a menüből majd a program.
     */
    void updateExit();

    /**
     * @brief Hozzáad egy új gombot a menühöz
     * Algoritmus leírása:
     * - Inkrementálja a számlálót
     * - Lefoglal 1-el több helyet és hozzáadja az új gombot
     * - Hozzáad 
     * @param extra Új gomb
     */
    void addButton(const Button& extra);

    /**
     * @brief Getter függvény a Gombra idx alapján
     * @param idx sorszám
     * @return buttonTömb[idx]-edik eleme
     */
    Button* getButton(int idx)const;

    /**
     * @brief Getter függvény a kilépés bool állapotára
     * 
     * @return true: Ha volt utasítás adva kilépésre 
     * @return false: Ha nem volt rá utasítás 
     */
    bool getExit()const;

    /**
     * @brief Getter az id adattagra.
     * Az id ilyenkor ebben az esetben már a Menü méretét is számon tartja.
     * @return Menü mérete
     */
    size_t getIdCounter()const;
};

#endif //NHF_REFORMED_MENU_H