/**
 * @file Computer.h
 * @brief A Computer osztályt tartalmazó header.
 */

#ifndef NHF_REFORMED_COMPUTER_H
#define NHF_REFORMED_COMPUTER_H
#include "Team.h"

/**
 * @brief Computer class az, aki kiszámolja a lehetséges lépéseket.
 * Megállapítja, hogy melyik csapat jön a játékban, majd kigyűjti a csapat lépéseit.
 */
class Computer {
public:
    /**
     * @brief Computer konstruktor.
     */
    Computer();

    /**
     * @brief A játékban következőként lépő csapat összes lehetséges lépését kiszámolja.
     * Algoritmus leírása:
     * - Megállapítja melyik csapat jön
     * - Majd annak a csapatnak az összes bábujának kiszámolja a lehetséges lépéseit, amiket minden bábu külön tárol egy saját listában.
     * - Ezeket a lépéseket belerakja a csapatnak a saját összesített lépés-listájába.
     * @param game Az éppen futó játék.
     */
    void calculateMoves(Game* game);

    /**
     * @brief A csapatnak az összesített lépés-listájából kiválasztja a legnagyobb súlyú lépést.
     * Ha a legnagyobb súlyú lépés értéke 0, akkor random választ az összes lépésből. Ha pedig több legnagyobb van, akkor azokból az legelső megtalálttal tér vissza.
     * @param game Az éppen futó játék.
     * @return A lépés amit a csapat fog lépni a játékban.
     */
    Move* decideMove(Game* game);
};
#endif //NHF_REFORMED_COMPUTER_H