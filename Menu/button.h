/**
 * @file button.h
 * @brief A Button osztályt tartalmazó header.
 */

#ifndef NHF_REFORMED_BUTTON_H
#define NHF_REFORMED_BUTTON_H
#include "../Game/Army.h"
#include "ButtonFunctionHandler.h"

/**
 * @brief A gomb class. Ezekből épülnek fel a menük.
 * Minden gombnak van egy id-je. Ezeket az id-ket a gombot tartalmazó Menü fogja kiosztani a gomboknak amilyen sorrendben jönnek.
 * Minden gomb tartalmaz egy funkciót ami futtathat menüt/szerkesztőt/játékot
 */
class Button{
private:
    size_t id;                              /**<A gomb sorszáma   */
    char* name;                             /**<A gomb neve  */
    ButtonFunctionHandler buttonFunction;   /**<A funkció amit a gomb tartalmaz  */

public:
    /**
     * @brief Alapértelmezett konstruktor.
     */
    Button();

    /**
     * @brief Paraméterezett konstruktor egyetlen függvénnyel.
     * @param name A gomb neve
     * @param id A gomb sorszáma
     * @param function A gombhoz rendelt függvény pointer
     */
    Button(const char* name,size_t id,void (*function)(std::ostream& ostream,std::istream& istream),std::ostream& os,std::istream& is);

    /**
     * @brief Paraméterezett konstruktor egy függvénnyel, és egy Army objektummal.
     * @param name A gomb neve
     * @param id A gomb sorszáma
     * @param functionArmy A gombhoz rendelt függvény pointer egy Army objektummal
     * @param armyPtr Az Army objektum pointer
     */
    Button(const char* name,size_t id,void (*functionArmy)(Army*,std::ostream& ostream,std::istream& istream),Army* armyPtr,std::ostream& os,std::istream& is);

    /**
     * @brief Paraméterezett konstruktor két függvénnyel és két Army objektummal.
     * @param name A gomb neve
     * @param id A gomb sorszáma
     * @param functionArmy A gombhoz rendelt függvény pointer két Army objektummal
     * @param armyPtr1 Az első Army objektum pointer
     * @param armyPtr2 A második Army objektum pointer
     */
    Button(const char* name,size_t id,void (*functionArmy)(Army* first,Army* second,std::ostream& ostream,std::istream& istream),Army* armyPtr1,Army* armyPtr2,std::ostream& os,std::istream& is);
    
    /**
     * @brief Destruktor.
     * Felszabadítja a dinamikusan foglalt gomb nevet.
     */
    ~Button();

    /**
     * @brief Másoló konstruktor.
     */
    Button(const Button& other);

    /**
     * @brief Értékadó operátor.
     */
    Button& operator=(const Button& other);

    /**
     * @brief Setter függvény az id-ra.
     * @param id Az új id
     */
    void setId(size_t idx);

    /**
     * @brief Getter függvény az id-ra. 
     * @return A gomb sorszáma
     */
    size_t getId()const;

    /**
     * @brief Getter függvény a névre.
     * @return A gomb neve
     */
    const char* getName()const;

    /**
     * @brief Gombhoz rendelt funkció lekérése.
     * @return A gombhoz rendelt funkció
     */
    ButtonFunctionHandler getFunction()const;
};
#endif //NHF_REFORMED_BUTTON_H