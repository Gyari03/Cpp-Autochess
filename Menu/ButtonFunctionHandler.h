/**
 * @file ButtonFunctionHandler.h
 * @brief A ButtonFunctionHandler osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_BUTTONFUNCTIONHANDLER_H
#define NHF_REFORMED_BUTTONFUNCTIONHANDLER_H
#include <iostream>

class Army;

/**
 * @brief Hozzákapcsolja a function-pointereket a gombokhoz.
 * Emellett lehetővé teszi, hogy több fajta függvényeket is tudjon futtatni egy gomb, akár olyanokat is amiknek más paramétereik vannak.
 */
struct ButtonFunctionHandler{
//private:
    void (*fun)(std::ostream& ostream,std::istream& istream);                                   /**<Függvénypointer ha nincsen army pointer hozzáadva az objektumhoz.  */
    void (*funArmy)(Army *army,std::ostream& ostream,std::istream& istream);                    /**<Függvénypointer ha 1db army pointer van hozzáadva az objektumhoz. */
    void (*funArmyFor2)(Army* army1, Army* army2,std::ostream& ostream,std::istream& istream);  /**<Függvénypointer ha 2db army pointer van hozzáadva az objektumhoz.  */

//public:
    std::ostream* os;
    std::istream* is;

//private:
    Army* regArmy1;                                 /**<Army1 pointer amit még a konstruktorban adhatunk hozzá */
    Army* regArmy2;                                 /**<Army2 pointer  */

//public:
    /**
     * @brief Destruktor
     */
    ~ButtonFunctionHandler(){}

    /**
     * @brief Az osztály alapértelmezett konstruktora.
     */
    ButtonFunctionHandler(std::ostream& os=std::cout,std::istream& is=std::cin): fun(nullptr), funArmy(nullptr), funArmyFor2(nullptr),os(&os),is(&is),regArmy1(nullptr), regArmy2(nullptr){}

    /**
     * @brief Konstruktor, amely egy függvényt kap paraméterül.
     * @param func Paraméternélküli függvénypointer. Ehhez nem kellenek seregek.
     */
    ButtonFunctionHandler(void (*func)(std::ostream& ostream,std::istream& istream),std::ostream& os,std::istream& is): fun(func), funArmy(nullptr), funArmyFor2(nullptr) ,os(&os),is(&is) , regArmy1(nullptr), regArmy2(nullptr){}
    
    /**
     * @brief Konstruktor, amely egy függvényt és egy Army objektum pointert kap paraméterül.
     * @param funcArmy Army paraméterrel rendelkező függvénypointer. Ennek már szüksége van egy seregre, hogy működjön.
     * @param armyPtr Az Army objektum pointer.
     */
    ButtonFunctionHandler(void (*funcArmy)(Army*,std::ostream& ostream,std::istream& istream), Army* armyPtr,std::ostream& os,std::istream& is): fun(nullptr), funArmy(funcArmy), funArmyFor2(nullptr) ,os(&os) ,is(&is) ,regArmy1(armyPtr), regArmy2(nullptr){}
    
    /**
     * @brief Konstruktor, amely két függvényt és két Army objektum pointert kap paraméterül.
     * @param funcArmy Két Army paraméterrel rendelkező függvénypointer. Ez olyan függvényeket futtat gombnyomásra, ahol 2 sereg is kell.
     * @param armyPtr1 Az első Army objektum pointer.
     * @param armyPtr2 A második Army objektum pointer.
     */
    ButtonFunctionHandler(void (*funcArmy)(Army*, Army*,std::ostream& ostream,std::istream& istream), Army* armyPtr1, Army* armyPtr2,std::ostream& os,std::istream& is): fun(nullptr), funArmy(nullptr), funArmyFor2(funcArmy), os(&os), is(&is),regArmy1(armyPtr1), regArmy2(armyPtr2){}
    
    /**
     * @brief Az objektum megfelelő függvényének végrehajtása.
     */
    void execute();
};

#endif //NHF_REFORMED_BUTTONFUNCTIONHANDLER_H

