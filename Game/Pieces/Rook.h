/**
 * @file Rook.h
 * @brief Rook osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_ROOK_H
#define NHF_REFORMED_ROOK_H
#include "../Piece.h"

/**
 * @brief Rook osztály, ami a bástyát reprezentálja a sakkjátékban.
 */
class Rook:public Piece {
public:
    /**
     * @brief Rook osztály konstruktora.
     * @param x Az oszlop koordinátája
     * @param y A sor koordinátája
     */
    Rook(int x,int y);

    /**
     * @brief Lehetséges lépéseket számolja ki a bástyának.
     * Tehát belerakja az orthogonális lépéseket kiszámoló függvényt.
     * @param game A játék objektumra mutató pointer
     */
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_ROOK_H