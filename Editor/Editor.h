/**
 * @file Editor.h
 * @brief Az Editor osztályt tartalmazó header.
 */

#ifndef NHF_REFORMED_EDITOR_H
#define NHF_REFORMED_EDITOR_H
#include "../Game/Army.h"
#include "../File Management/Filemanagement.h"
#include <sstream>
#include <string>

/**
 * @brief A seregek létrehozásáért és szerkesztéséért felelős osztály.
 */
class Editor {
    
private:
    Army* army;     /**< Pointer az éppen szerkesztett seregre. */
    bool exit;      /**< Logikai érték arra, hogy a felhasználó végzett-e a sereg szerkesztésével. Ha igaz, akkor az editor visszalép a menübe. */
    bool toDelete;  /**< Logikai érték arra, hogy ha a felhasználó szeretné törölni a sereget. */

public:
    /**
     * @brief Default konstruktor.
     * Ha a felhasználó új sereget szeretne létrehozni.
     */
    Editor();

    /**
     * @brief Destruktor.
     * Felszabadítja a dinamikusan foglalt sereget.
     */
    ~Editor();

    /**
     * @brief Paraméteres konstruktor.
     * Egy meglévő sereget szerkeszt.
     * @param army Pointer arra a dinamikusan foglalt seregre amit szerkesztünk.
     */
    Editor(Army* army);

    /**
     * @brief Getter függvény az éppen szerkesztett sereg pointerére.
     * @return Az éppen szerkesztett sereg pointere.
     */
    Army* getArmy() const;

    /**
     * @brief Keres egy bábut a megadott x-y koordinátákon.
     * @param coordX A keresett mező x koordinátája.
     * @param coordY A keresett mező y koordinátája.
     * @return Pointer a keresett bábura. Ha nincsen bábu a keresett mezőn akkor nullptr a visszatérési érték.
     */
    Piece* searchFor(int coordX, int coordY);

    /**
     * @brief Frissíti a kilépési boolt. Ha hamis volt igazzá teszi.
     */
    void updateExit();

    /**
     * @brief Getter függvény a kilépési boolra.
     * @return Igaz, ha a szerkesztőből ki kell lépni, egyébként hamis.
     */
    bool getExit() const;

    /**
     * @brief Elrendelteti az éppen szerkesztett seregnek a törlését a lementett seregek közül.
     */
    void updateDelete();

    /**
     * @brief Getter függvény a törlési bool-ra.
     * @return Igaz, ha a szerkesztett sereget törölni kell, egyébként hamis.
     */
    bool getDelete() const;

    /**
     * @brief Elmenti az újonnan készült sereget.
     * Kimenti az armies.txt-be leghátulra.
     */
    void saveArmy();

    /**
     * @brief Elmenti az éppen szerkesztett sereg változtatásait.
     * Átírja az armies.txt-ben a sereget a legújabb verziójával.
     */
    void editArmy();

    /**
     * @brief Kitörli az éppen szerkesztett sereget.
     * Kitörli az armies.txt-ben a sereget.
     */
    void deleteArmy();
};
#endif //NHF_REFORMED_EDITOR_H