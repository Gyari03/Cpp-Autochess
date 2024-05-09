#include "Army.h"
#include <iostream>
#include "../Memtrace/memtrace.h"

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

Piece* Army::getPiece(int x, int y){ //megnézi hogy van-e a mezőn valaki
    for (int i = 0; i < pieces.getSize(); ++i) {
        if(pieces[i]->getcoordX()==x && pieces[i]->getcoordY()==y){
            return pieces[i];
        }
    }
    return nullptr;
}

bool Army::partOfArmy(Piece *piece) {
    for (int i = 0; i < pieces.getSize(); ++i) {
        if(pieces[i]==piece){
            return true;
        }
    }
    return false;
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

void copyArmy(Army* source, Army* destination) {
    int currentX;
    int currentY;
    char currentName;
    Piece* currentPiece;
    for(int i = 0; i < source->getsizeofArmy(); i++) {
        currentX = source->getPiece(i)->getcoordX();
        currentY = source->getPiece(i)->getcoordY();
        currentName = source->getPiece(i)->getname();
        currentPiece = createPiece(currentName, currentX, currentY);
        destination->addPiece(*currentPiece);
    }
   // delete source;
}

void mirrorArmy(Army* army) {
    int currentY;
    for (int i = 0; i < army->getsizeofArmy(); i++) {
        //x koordinátákat hagyjuk nem kell azt mozgatni
        currentY = army->getPiece(i)->getcoordY();
        army->getPiece(i)->setcoordY(  9-currentY);
        //army->getPiece(i)->setcoordY(7-currentY);
        army->getPiece(i)->tolowercase();
    }
}