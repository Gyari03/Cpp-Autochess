#ifndef NHF_REFORMED_TEAM_H
#define NHF_REFORMED_TEAM_H
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
    TeamColor teamColor;
    Army army;
    Piece** pieces;
public:
    void convert_army();



};


#endif //NHF_REFORMED_TEAM_H
