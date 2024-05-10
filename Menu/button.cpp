#include "button.h"
#include <cstring>

#include "../Memtrace/memtrace.h"

Button::Button():id(0),name(nullptr),buttonFunction(){}

Button::Button(const char* name,size_t id,void (*function)()):id(id),buttonFunction(function) {
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}

Button::Button(const char *name, size_t id, void (*functionArmy)(Army *),Army* armyPtr):buttonFunction(functionArmy,armyPtr) {
    this->id=id;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}

Button::Button(const char *name, size_t id, void (*functionArmy)(Army* first, Army* second), Army *armyPtr1,Army* armyPtr2): buttonFunction(functionArmy,armyPtr1,armyPtr2) {
    this->id=id;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}



Button::~Button() {
    delete[] name;
}

Button::Button(const Button &other) {
    this->id=other.id;
    this->name=new char[strlen(other.name)+1];
    strcpy(this->name,other.name);
    this->buttonFunction=other.buttonFunction;
}

Button &Button::operator=(const Button &other) {
    if(this!=&other){
        delete[] this->name;
        this->id=other.id;
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->buttonFunction=other.buttonFunction;
    }
    return *this;
}

void Button::setId(size_t id) {
    this->id=id;
}

size_t Button::getId()const {
    return this->id;
}

const char* Button::getName()const{
    return name;
}

ButtonFunction Button::getFunction()const {
    return this->buttonFunction;
}


