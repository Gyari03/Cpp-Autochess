/**
 * @file King.h
 * @brief King osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_KING_H
#define NHF_REFORMED_KING_H
#include "../Piece.h"

/**
 * @brief King osztály, ami a királyt reprezentálja a sakkjátékban.
 * Ebből a bábuból minden csapatnak kell, hogy legyen különben automatikusan veszt. Ez a játék feltétele. Ebből lehet több egy csapatban.
 */
class King:public Piece {
public:

    /**
     * @brief King osztály konstruktora.
     * @param x Az oszlop koordinátája
     * @param y A sor koordinátája
     */
    King(int x,int y);

    /**
     * @brief Lehetséges lépéseket számolja ki a királynak.
     * A külön erre elkészített kingMove() fv.-t használja.
     * @param game A játék objektumra mutató pointer
     */
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_KING_H