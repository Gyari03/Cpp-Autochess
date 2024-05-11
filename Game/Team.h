/**
 * @file Team.h
 * @brief A Team osztályt és TeamColor-t tartalmazó header
 */

#ifndef NHF_REFORMED_TEAM_H
#define NHF_REFORMED_TEAM_H
#include "../List/List.hpp"
#include "Piece.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/Pawn.h"
#include "Pieces/Horse.h"
#include "Pieces/Bishop.h"
#include "Pieces/Rook.h"
#include "Army.h"
#include "Piece.h"

/**
 * @brief A csapatszínek lehetséges értékei
 */
enum TeamColor{White,Black};


/**
 * @brief A Team class. Ebből jön létre 2 db amikor elindul a játék-szimuláció.
 * Ide vannak kigyűjtve a seregek lépései miután a bábuk összegyűjtötték a lehetséges lépéseiket.
 */
class Team {
private:
    List<Move> teamMoves;   /**< Csapat lépéseinek az összesített listája.  */
    TeamColor teamColor;    /**< Csapat színe.  */
    Army* ownArmy;          /**< A sereg amiből a csapat áll.  */
public:

    /**
     * @brief Team konstruktor
     * Ha a színe fekete, akkor a bábuit feltükrözi.
     * A seregre a helyet dinamikusan lefoglalja és átmásolja oda a paraméterként kapott Armyból a bábukat.
     * @param army A sereg amivel a csapat fog játszani.
     * @param color A csapat színe.
     */
    Team(Army* army,TeamColor color);

    /**
     * @brief Team destruktor
     * Felszabadítja a dinamikusan lefoglalt seregét.
     */
    ~Team();

    /**
     * @brief Getter függvény a csapaton belüli seregre.
     * @return Seregére mutató pointer
     */
    Army* getArmy();
    
    /**
     * @brief Getter függvény a csapat összesített lépéseinek listájára.
     * @return Összesített lépések listája.
     */
    List<Move>& getTeamMoves();

    /**
     * @brief Random lépést kiválaszt a lépések listájából, ha nincsen maximum.
     * @return Random lépés.
     */
    Move* getRandomMove();

    /**
     * @brief Megszámolja azt, hogy hány király van egy csapatban.
     * Azért fontos, mert ha 0 van egy csapatban akkor a csapat vesztett. Ez minden körben lefut.
     * @return Királyok darabaszáma egy csapatban.
     */
    int countAmountOfKigns();
};
#endif //NHF_REFORMED_TEAM_H