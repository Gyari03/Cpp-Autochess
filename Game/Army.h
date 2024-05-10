#ifndef NHF_REFORMED_ARMY_H
#define NHF_REFORMED_ARMY_H
#include "Piece.h"
#include <cstring>

class Army {
private:
    char nameofArmy[35];
    int sizeofArmy;
    List<Piece> pieces;

public:
    Army();
    ~Army();
    const char* getnameofArmy()const;
    void setnameofArmy(const char* name);
    int getsizeofArmy()const;
    void setsizeofArmy(int size);
    void incrementsizeofArmy();
    void addPiece(Piece& newPiece);
    void deletePiece(int coordX, int coordY);
    Piece* getPiece(int coordX, int coordY);
    bool partOfArmy(Piece* piece);
    Army(const Army& army); //cpyconstructor
    Army& operator=(const Army& army);
    Piece* getPiece(size_t idx);
    static void copyArmy(Army* source, Army* destination);
    static void mirrorArmy(Army* army);
};
#endif //NHF_REFORMED_ARMY_H