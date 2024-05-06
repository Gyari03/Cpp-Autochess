#include "Army.h"
#include <iostream>

Army::Army():nameofArmy(""),sizeofArmy(0){}

Army::~Army() {
}

const char* Army::getnameofArmy()const{
    return nameofArmy;
}

void Army::setnameofArmy(const char *name) { //még kell egy felület ahol aktiválódik
    if (name != nullptr) {
        strncpy(this->nameofArmy, name, sizeof(this->nameofArmy) - 1);
        this->nameofArmy[sizeof(this->nameofArmy) - 1] = '\0';
    }
}

int Army::getsizeofArmy() const {
    return sizeofArmy;
}

void Army::setsizeofArmy(int size) {
    sizeofArmy=size;
}

void Army::incrementsizeofArmy() {
    sizeofArmy++;
}


//Ezt ui-n belül függvénybe foglalni: 1)Megnézni létezik ilyen, ha igen:kitörölni 2)beilleszteni helyére
void Army::addPiece(Piece& newPiece) {

    //hibakezelés túl nagy index esetén:
    if(newPiece.getcoordX()>8 || newPiece.getcoordY()>4){
        Piece* ptr = &newPiece; //rámutatás, hogy fel tudjam szabadítani mivel ez nem kerül bele a listbe ahonnan felszabadulnakk
        delete ptr;
        return;
    }

    if(this->getPiece(newPiece.getcoordX(),newPiece.getcoordY())!=nullptr){
        this->pieces.deletefromList(getPiece(newPiece.getcoordX(),newPiece.getcoordY()));
        sizeofArmy--;
    }
    this->pieces.addtoList(&newPiece);
    sizeofArmy++;
}



void Army::deletePiece(int x,int y) {
    if(this->getPiece(x,y)!=nullptr){
        this->pieces.deletefromList(getPiece(x,y));
        sizeofArmy--;
    }
}



Army::Army(const Army &army){
    strncpy(this->nameofArmy, army.getnameofArmy(), sizeof(this->nameofArmy) - 1);
    this->nameofArmy[sizeof(this->nameofArmy) - 1] = '\0';
    this->sizeofArmy=army.sizeofArmy;
    this->pieces=army.pieces;
}

Army& Army::operator=(const Army& army) {
    if (this != &army){
        this->setnameofArmy(army.getnameofArmy());
        this->setsizeofArmy(army.getsizeofArmy());
        this->pieces=army.pieces;
    }
    return *this;
}

