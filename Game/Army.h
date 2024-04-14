#ifndef NHF_REFORMED_ARMY_H
#define NHF_REFORMED_ARMY_H
#include "Piece.h"
#include <cstring>

class Army { //alapfelállás ami be van adva a csapatnak, majd ezt dinamikusan átmásolja magának
private:
    char nameofArmy[35];
    int sizeofArmy; //nincs megcsinálva rendesen
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
    Piece* getPiece(int x,int y){
        for (int i = 0; i < pieces.getSize(); ++i) {
            if(pieces[i]->getcoordX()==x && pieces[i]->getcoordY()==y){
                return pieces[i];
            }
        }
        return nullptr;
    }

    Army(const Army& army); //cpyconstructor
    Army& operator=(const Army& army);


    Piece* getPiece(int idx){ //fontos, hogy az index ne legyen több mint a mennyiségük
        return pieces[idx];
    }
};

//txt ui fuggvenyek

void addArmy();
void deleteArmy();


//-------------------armies.txt-------------------
//int n                                                     <--number of armies represented  allocate this
//Char* army1                                               <--name of first army            these too
//int m                                                     <-- number of soldiers inside army1
//K[x][y]Q[x][y]R[x][y]H[x][y]H[x][y]H[x][y]H[x][y]B[x][y]  <--All the militants of the army
//Char* army2                                               <--name of first army
//int m                                                     <-- number of soldiers inside army2
//K[x][y]Q[x][y]R[x][y]H[x][y]H[x][y]H[x][y]H[x][y]B[x][y]  <--All the militants of the army
//.
//.
//...


#endif //NHF_REFORMED_ARMY_H
