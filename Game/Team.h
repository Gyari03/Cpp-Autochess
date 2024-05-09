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
    List<Move> teamMoves;
    TeamColor teamColor;
    Army* ownArmy; //Ez viszont egy újonnan lefoglalt army
public:
    Team(Army* army,TeamColor color);
    Army* getArmy();
    List<Move>& getTeamMoves();
  //  Move* getRandomMove();
};


#endif //NHF_REFORMED_TEAM_H
