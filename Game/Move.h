/**
 * @file Move.h
 * @brief A Move osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_MOVE_H
#define NHF_REFORMED_MOVE_H

class Piece;


/**
 * @brief A Move class. Ezt tárolják el a bábuk, emellett csapatok listákban.
 */
class Move {
private:
    Piece* originPiece;                 /**< A bábu aki meg tudja tenni a lépést.  */
    int destinationX, destinationY;     /**< A mező ahova léphet a bábu. */
    char destinationPieceName;          /**< A mezőn elhelyezkedő ellenséges Bábu neve. Ha üres a mező akkor '0' van használva. */
    int weight;                         /**< Az adott mező súlya, attól függ, hogy milyen bábu helyezkedik el a célmezőn.  */

public:

    /**
     * @brief Move konstruktor
     * Miután inicializál minden értéket(kivéve Weight) lefut benne a calculateWeight() amiből megkapja a súlyozását.
     * @param originPiece A bábu aki meg tudja tenni a lépést.
     * @param coordX Az adott mező x koordinátája.
     * @param coordY Az adott mező y koordinátája.
     * @param destinationPieceName Az adott mezőn elhelyezkedő ellenséges bábu.
     */
    Move(Piece* originPiece, int coordX, int coordY, char destinationPieceName=0);

    /**
     * @brief Move destruktor
     */
    ~Move();

    /**
     * @brief Kiszámolja egy Move objektum súlyát.
     * Úgy számolja ki, hogy minél értékesebb a bábu a célmezőn annál nagyobb súlyt ad.
     */
    void calculateWeight();

    /**
     * @brief Nagyobb operátor
     * Eldönti, hogy nagyobb-e jobboldali Move-nál nagyobb súly alapján.
     * @param otherMove Jobb oldali Move érték
     * @return true:  Bal oldali érték nagyobb
     * @return false: Jobb oldali érték nagyobb
     */
    bool operator>(const Move& otherMove) const;

    /**
     * @brief Getter függvény az originPiece-re. 
     * Rámutat arra a Piece-re akiből származik.
     * @return Piece* 
     */
    Piece* getPiece()const;

    /**
     * @brief Getter függvény x koordinátára
     * @return x koordináta
     */
    int getCoordX()const;

    /**
     * @brief Getter függvény y koordinátára
     * @return y koordináta
     */
    int getCoordY()const;

    /**
     * @brief Getter függvény a lépés súlyára
     * @return Lépés súlya
     */
    int getWeight()const;
};
#endif //NHF_REFORMED_MOVE_H