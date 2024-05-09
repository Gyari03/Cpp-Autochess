#ifndef NHF_REFORMED_ARMY_H
#define NHF_REFORMED_ARMY_H
#include "Piece.h"
#include <cstring>

class Army { //alapfelállás ami be van adva a csapatnak, majd ezt dinamikusan átmásolja magának
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
    void deletePiece(int x,int y);
    Piece* getPiece(int x,int y);
    bool partOfArmy(Piece* piece);
    Army(const Army& army); //cpyconstructor
    Army& operator=(const Army& army);
    Piece* getPiece(int idx){ //fontos, hogy az index ne legyen több mint a mennyiségük
        return pieces[idx];
    }
};

void copyArmy(Army* source, Army* destination);

void mirrorArmy(Army* army);

#endif //NHF_REFORMED_ARMY_H
