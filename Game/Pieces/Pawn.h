/**
 * @file Pawn.h
 * @brief Pawn osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_PAWN_H
#define NHF_REFORMED_PAWN_H
#include "../Piece.h"

/**
 * @brief Pawn osztály, ami a gyalogot reprezentálja a sakkjátékban.
 */
class Pawn:public Piece {
public:
    /**
     * @brief Pawn osztály konstruktora.
     * @param x Az oszlop koordinátája
     * @param y A sor koordinátája
     */
    Pawn(int x,int y);

    /**
     * @brief Lehetséges lépéseket számolja ki a gyalognak.
     * A külön erre elkészített pawnMove() fv.-t használja.
     * @param game A játék objektumra mutató pointer
     */
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_PAWN_H