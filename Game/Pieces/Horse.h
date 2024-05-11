#ifndef NHF_REFORMED_HORSE_H
#define NHF_REFORMED_HORSE_H
#include "../Piece.h"


/**
 * @file Horse.h
 * @brief Horse osztályt tartalmazó header
 */
class Horse:public Piece {
public:

     /**
     * @brief Horse osztály konstruktora.
     * @param x Az oszlop koordinátája
     * @param y A sor koordinátája
     */
    Horse(int x,int y);

     /**
     * @brief Lehetséges lépéseket számolja ki a lónak.
     * Az erre külön elkészített horseMove()-t használja.
     * @param game A játék objektumra mutató pointer
     */
    void calculateMoves(Game* game) override;
};
#endif //NHF_REFORMED_HORSE_H