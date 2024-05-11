/**
 * @file Bishop.h
 * @brief Bishop osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_BISHOP_H
#define NHF_REFORMED_BISHOP_H
#include "../Piece.h"

/**
 * @brief Bishop osztály, ami a futót reprezentálja a sakkjátékban.
 */
class Bishop:public Piece{
public:

    /**
     * @brief Bishop osztály konstruktora.
     * @param x Az oszlop koordinátája
     * @param y A sor koordinátája
     */
    Bishop(int x,int y);

    /**
     * @brief Lehetséges lépéseket számolja ki a futónak.
     * A lépések kiszámolására az elkészített diagonal() -átlós lépések függvényét használja
     * @param game A játék objektumra mutató pointer
     */
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_BISHOP_H