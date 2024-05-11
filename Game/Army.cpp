#include "Army.h"
#include <iostream>
#include "../Memtrace/memtrace.h"
#include <cstring>

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


void Army::addPiece(Piece& newPiece) {

    //hibakezelés túl nagy index esetén:
    if(newPiece.getCoordX() > 8 || newPiece.getCoordY() > 4){
        Piece* ptr = &newPiece; //rámutatás, hogy fel tudjam szabadítani mivel ez nem kerül bele a listbe ahonnan felszabadulnakk
        delete ptr;
        return;
    }

    if(this->getPiece(newPiece.getCoordX(), newPiece.getCoordY()) != nullptr){
        this->pieces.deletefromList(getPiece(newPiece.getCoordX(), newPiece.getCoordY()));
        sizeofArmy--;
    }
    this->pieces.addtoList(&newPiece);
    sizeofArmy++;
}



void Army::deletePiece(int coordX, int coordY) {
    if(this->getPiece(coordX, coordY) != nullptr){
        this->pieces.deletefromList(getPiece(coordX, coordY));
        sizeofArmy--;
    }
}

Piece* Army::getPiece(int coordX, int coordY){ //megnézi hogy van-e a mezőn valaki
    for (int i = 0; i < pieces.getSize(); ++i) {
        if(pieces[i]->getCoordX() == coordX && pieces[i]->getCoordY() == coordY){
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

Piece* Army::getPiece(size_t idx){ //fontos, hogy az index ne legyen több mint a mennyiségük
    return pieces[idx];
}

void Army::copyArmy(Army* source, Army* destination) {
    strcpy(destination->nameofArmy,source->nameofArmy);
    int currentX;
    int currentY;
    char currentName;
    Piece* currentPiece;
    for(int i = 0; i < source->getsizeofArmy(); i++) {
        currentX = source->getPiece(i)->getCoordX();
        currentY = source->getPiece(i)->getCoordY();
        currentName = source->getPiece(i)->getName();
        currentPiece = Piece::createPiece(currentName, currentX, currentY);
        destination->addPiece(*currentPiece);
    }
}

void Army::mirrorArmy(Army* army) {
    int currentY;
    for (int i = 0; i < army->getsizeofArmy(); i++) {
        //destinationX koordinátákat hagyjuk nem kell azt mozgatni
        currentY = army->getPiece(i)->getCoordY();
        army->getPiece(i)->setCoordY(9 - currentY);
        army->getPiece(i)->toLowercase();
    }
}