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

enum TeamColor{White,Black};


class Team {
private:
    List<Piece> pieces;
    List<Move> teamMoves;
    TeamColor teamColor;
    Army army;
public:
   // Team(Army army;TeamColor color);

};


#endif //NHF_REFORMED_TEAM_H
