/**
 * @file Army.h
 * @brief Az Army osztályt tartalmazó header.
 */

#ifndef NHF_REFORMED_ARMY_H
#define NHF_REFORMED_ARMY_H
#include "Piece.h"
#include <cstring>

/**
 * @brief Sereg class és annak a függvényei
 */
class Army {
private:
    char nameofArmy[36];    /**< A sereg nevét tároló char tömb. Maximum 35 karakteres. */
    int sizeofArmy;         /**< A sereg mérete */
    List<Piece> pieces;     /**< A sereg bábuinak a listája*/

public:
    /**
     * @brief Sereg default konstruktora.
     * A méretét 0-ra állítja és egy üres-sztringet állít be a nevére.
     */
    Army();

    /**
     * @brief Army objektum destuktora.
     * Ebben felszabadul a bábuk listája amiben dinamikusan vannak tárolva a bábuk
     */
    ~Army();

    /**
     * @brief Getter függvény a sereg nevére.
     * @return A sereg neve.
     */
    const char* getnameofArmy()const;

    /**
     * @brief Setter függvény a sereg nevére.
     * @param name Beállítandó név.
     */
    void setnameofArmy(const char* name);

    /**
     * @brief Getter függvény a sereg méretére.
     * @return A sereg mérete.
     */
    int getsizeofArmy()const;

    /**
     * @brief Setter függvény a sereg méretére.
     * @param size Beállítandó méret.
     */
    void setsizeofArmy(int size);

    /**
     * @brief Sereg méretének megnövelése 1-el.
     */
    void incrementsizeofArmy();

    /**
     * @brief Bábu hozzáadása a sereghez.
     * Ha az adott bábunak túl nagyok az indexei, akkor nem adódik hozzá a sereghez.
     * @param newPiece Új bábu
     */
    void addPiece(Piece& newPiece);

    /**
     * @brief Bábu eltávolítása a seregből.
     * Koordináta alapján megadott bábu kitörlése. Ha nincs az adott mezőn bábu akkor nem töröl ki semmit.
     * @param coordX Eltávolítandó bábu x koordinátája.
     * @param coordY Eltávolítandó bábu y koordinátája.
     */
    void deletePiece(int coordX, int coordY);

    /**
     * @brief Getter függvény egy Piece-re mutató pointerért adott koordináták alapján.
     * Keres a seregben az adott koordinátákon egy bábut és visszatér egy rámutató pointerrel. Amennyiben nincs ilyen bábu nullptr-el tér vissza.
     * @param coordX Keresett bábu x koordinátája.
     * @param coordY Keresett bábu y koordinátája.
     * @return Piece* Keresett bábura mutató pointer.
     */
    Piece* getPiece(int coordX, int coordY);

    /**
     * @brief Logikai érték arra, hogy egy adott bábu része-e egy seregnek.
     * Ezt leginkább a szimulációban használják a csapatok, hogy megállapítsák, hogy egy adott bábu szövetséges-e.
     * @param piece Bábura mutató pointer
     * @return true: Része a seregnek 
     * @return false: Nem része a seregnek 
     */
    bool partOfArmy(Piece* piece);

    /**
     * @brief Sereg másolókonstruktor
     * @param army Lemásolandó sereg
     */
    Army(const Army& army); 

    /**
     * @brief Sereg másolóoperátor
     * @param army Lemásolandó sereg.
     * @return Army& Lemásolt sereg referenciája.
     */
    Army& operator=(const Army& army);

    /**
     * @brief Getter függvény csapaton belüli i-edik bábunak.
     * Leginkább arra van, hogy ciklusban végigmenjünk a csapaton és minden bábuhoz hozzáférhessünk.
     * @param idx Bábu indexe a listában.
     * @return Bábura mutató pointer.
     */
    Piece* getPiece(size_t idx);

    /**
     * @brief Két paraméterként kapott sereg-pointerek között egyikből átmásol a másikba.
     * @param source 
     * @param destination 
     */
    static void copyArmy(Army* source, Army* destination);

    /**
     * @brief Áttükrözi egy seregnek a bábuit a másik térfélre.
     * Szerkesztőben csak egy darab térfelet szerkesztünk, viszont a játék 2 összeillesztett térfél, ahol az egyik csapat fel van tükrözve a tábla tetejére.
     * Az algoritmus nem tesz többet, mint a sereg összes bábujának az Y koordinátáját kivonja 9-ből. Emellett kisbetűssé teszi a bábuk betűjelét, ezzel jelezve, hogy a fekete csapatba tartoznak.
     * @param army A feltükrözendő sereg.
     */
    static void mirrorArmy(Army* army);
};
#endif //NHF_REFORMED_ARMY_H