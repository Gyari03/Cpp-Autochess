/**
 * @file Piece.h
 * @brief Piece osztályt és a lépésüket kiszámoló statikus függvények headerje
 */

#ifndef NHF_REFORMED_PIECE_H
#define NHF_REFORMED_PIECE_H
#include "../List/List.hpp"
#include "Move.h"

class Game;


/**
 * @brief Bábu osztály.
 * Ez egy absztrakt osztály, amiből az összes sakkbábu osztály öröklődik.
 * Belőlük épülnek fel a seregek.
 */
class Piece {
private:
    int y,x;                    /**< Bábu koordinátái  */
    char name;                  /**< Bábu "neve", ami egy szimpla 1 karakter ami a betűjelét tárolja.  */

protected:
    List<Move> piece_moves;     /**< A bábu lépéseit tároló lista  */

public:
    /**
     * @brief Bábu konstruktor. 
     * @param name Bábu neve.
     * @param coordX Bábu x koordinátája.
     * @param coordY Bábu y koordinátája.
     */
    Piece(char name, int coordX=0, int coordY=0);

    /**
     * @brief Bábu destruktor.
     * Amikor lefut akkor felszabadul a listája ami tárolja a lehetséges lépéseit(Persze, csak ha játékban van, mivel csak akkor vannak számolva a lépései).
     */
    virtual ~Piece(){}

    /**
     * @brief Getter függvény az y koordinátára.
     * @return Bábu y koordinátája.
     */
    int getCoordY()const;

    /**
     * @brief Getter függvény az x koordinátára.
     * @return Bábu x koordinátája.
     */
    int getCoordX()const;

    /**
     * @brief Getter függvény a bábu nevére.
     * @return Bábu neve.
     */
    char getName()const;

    /**
     * @brief Getter függvény a bábu lépéseinek a listájára.
     * @return Bábu lépéseinek listája.
     */
    List<Move>& getMoves();

    /**
     * @brief Setter függvény a bábu Y koordinátájának.
     * @param newY Új y koordináta érték.
     */
    void setCoordY(int newY);

    /**
     * @brief  Setter függvény a bábu x koordinátájának.
     * @param newX Új x koordináta érték.
     */
    void setCoordX(int newX);

    /**
     * @brief Egyenlőség operátor
     * @param otherPiece Jobboldali Piece referencia
     * @return true: Ha ugyanazon a mezőn vannak akkor igazat ad.
     * @return false: Ha különböző mezőkön állnak akkor hamis.
     */
    bool operator==(const Piece& otherPiece)const;

    /**
     * @brief Átváltja egy bábunak a nevét kisbetűsre nagybetűsről.
     * Ezt a tükrözésnél használja a program.
     */
    void toLowercase();

    /**
     * @brief Kiszámolja egy bábu lépéseit
     * Viszont tisztán virtuális, tehát majd az ebből a classból öröklődő osztályok fogják megvalósítani.
     * @param game Játék objektumra mutató pointer.
     */
    void virtual calculateMoves(Game* game)=0;

    /**
     * @brief Hozzáad egy dinamikusan foglalt Move objektumot a meglévő Piecenek a Move listájához.
     * Ezt a függvényt majd a checkAndAddMove(...) használja majd.
     * @param destinationPieceName A célmezőn lévő bábu neve.
     * @param coordX A célmező x koordinátája.
     * @param coordY A célmező Y koordinátája.
     */
    void addMove(char destinationPieceName, int coordX, int coordY);

    /**
     * @brief Létrehoz egy Piece objektumot.
     * Név alapján hozza létre a bábut. Ha rossz nevet kap, akkor nullptr-t ad vissza.
     * @param name Létrehozandó bábu neve. Ez alapján dönti el, hogy milyen konstruktort futtasson le a bábunak.
     * @param x A bábu x koordinátája.
     * @param y A bábu y koordinátája.
     * @return Létrehozott bábura mutató pointer.
     */
    static Piece* createPiece(char name,int x,int y);

    /**
     * @brief Kiszámolja, hogy adott mezőre léphet-e a Bábu. Ha igen akkor hozzáadja a lépéseihez.
     * Emellett visszatér egy bool value-val, mivel a legtöbb bábu egy hosszabb vonalban lép.
     * - Ha hamissal tér vissza, akkor megszakad a vonal amiben tud lépni. Ami azt jelenti, hogy a vonal útját állja valami. És a ló kivételével nem is léphet át semmi a másikon.
     * @param game Game objektum pointer.
     * @param originPiece A bábu akiből a lépés származik.
     * @param posX A célmező x koordinátája.
     * @param posY A célmező y koordinátája.
     * @return true: Elállta valami az útját.(lehet az ellenség[akkor leüthető] vagy csapattárs[akkor nem üthető]) Ha ciklusban volt nem mehet tovább. 
     * @return false: Nem állta semmi az útját. Ha ciklusban van mehet tovább. 
     */
    static bool checkAndAddMove(Game* game, Piece* originPiece, int posX, int posY);

    /**
     * @brief Felfelé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void upwards(Piece* originPiece, Game* game);//Észak,dél,kelet,nyugat

    /**
     * @brief Lefelé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void downwards(Piece* originPiece, Game* game);

    /**
     * @brief Jobbrafelé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void rightwards(Piece* originPiece, Game* game);

    /**
     * @brief Balrafelé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void leftwards(Piece* originPiece, Game* game);

    /**
     * @brief Északkelet felé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void diagonalUpRight(Piece* originPiece, Game* game);//ÉK,ÉNY,DK,DNY

    /**
     * @brief Északnyugat felé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void diagonalUpLeft(Piece* originPiece, Game* game);

    /**
     * @brief Délkelet felé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void diagonalDownRight(Piece* originPiece, Game* game);

    /**
     * @brief Délnyugat felé egy vonalban az összes lépés a bábu pozíciójától.
     * Addig megy amíg el nem állja valami az útját vagy ki nem indexel.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer. 
     */
    static void diagonalDownLeft(Piece* originPiece, Game* game);

    /**
     * @brief Ortogonális lépések(+) 
     * Így lép például a bástya. Ez pedig az upwards(),downwards(),rightwards(),leftwards() függvények összesítése.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer.
     */
    static void orthogonal(Piece* originPiece, Game* game);

    /**
     * @brief Átlós lépések(X)
     * Így lép például a futó. Ez pedig a diagonalDownLeft(),diagonalDownRight(),diagonalUpLeft(),diagonalUpRight() függvények összesítése.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer.
     */
    static void diagonal(Piece* originPiece, Game* game);

    /**
     * @brief Parasztlépés.
     * Algoritmus leírása:
     * - Először eldöntjük, hogy melyik színben vagyunk, mivel a fekete parasztok csak lefele, a fehér pedig felfele tud lépni
     * - A paraszt előtti mezőt hozzáadjuk a lépéseihez, ha nincsen elfoglalva
     * - Majd megnézzük, hogy az amellett lévő 2 szomszédos mező üthető-e egyébként, ha igen, akkor hozzáadjuk a lépéseihez.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game  Game objektumra mutató pointer.
     */
    static void pawnMove(Piece* originPiece, Game* game);

    /**
     * @brief Lólépés.
     *  Ló bábú lépéseinek ellenőrzése és hozzáadása a lehetséges lépésekhez.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game Game objektumra mutató pointer.
     */
    static void horseMove(Piece* originPiece, Game* game);

    /**
     * @brief Királylépés. 
     * ellenőrzi a megadott király bábú lehetséges lépéseit a táblán, majd hozzáadja azokat a lehetséges lépések listájához.
     * @param originPiece A bábu akiből származik a lépés.
     * @param game Game objektumra mutató pointer.
     */
    static void kingMove(Piece* originPiece, Game* game);
};
#endif //NHF_REFORMED_PIECE_H