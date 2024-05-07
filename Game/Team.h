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

enum TeamColor{White,Black};


class Team {
private:
    List<Piece> pieces;
    List<Move> teamMoves;
    TeamColor teamColor;
  //  Army* sourceArmy; //Ez az army a menüben fel lesz szabadítva, erre nem is tervezünk hivatkozni
    Army* ownArmy; //Ez viszont egy újonnan lefoglalt army
public:
    Team(Army* army,TeamColor color):teamColor(color){
        copyArmy(army,ownArmy);
        if(teamColor == Black){
            mirrorArmy(ownArmy);
        }
    }
    Army* getArmy()const{
        return ownArmy;
    }
};


#endif //NHF_REFORMED_TEAM_H
