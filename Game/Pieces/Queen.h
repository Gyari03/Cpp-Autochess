/**
 * @file Queen.h
 * @brief Queen osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_QUEEN_H
#define NHF_REFORMED_QUEEN_H
#include "../Piece.h"

/**
 * @brief Queen osztály, ami a vezért reprezentálja a sakkjátékban.
 */
class Queen:public Piece {
public:
    /**
     * @brief Queen osztály konstruktora.
     * @param x Az oszlop koordinátája
     * @param y A sor koordinátája
     */
    Queen(int x,int y);

    /**
     * @brief Lehetséges lépéseket számolja ki a vezérnek.
     * Ezek a lépések együtt az orthogonális és az átlós lépések kombinálva.
     * @param game A játék objektumra mutató pointer
     */
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_QUEEN_H