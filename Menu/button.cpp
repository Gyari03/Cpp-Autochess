#include "button.h"
#include <cstring>

Button::Button():id(0),name(nullptr),buttonFunction(){}

Button::Button(const char* name,int id,void (*function)()):buttonFunction(function) {
    this->id=id;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
 /*   this->fun=fun;

    this->funArmy=nullptr;*/
}

Button::Button(const char *name, unsigned int id, void (*functionArmy)(Army *),Army* armyPtr):buttonFunction(functionArmy,armyPtr) {
    this->id=id;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    /*this->funArmy = funArmy;

    this->fun = nullptr;*/
}

Button::Button(const char *name, unsigned int id, void (*functionArmy)(Army *, Army *), Army *armyPtr1,Army* armyPtr2): buttonFunction(functionArmy,armyPtr1,armyPtr2) {
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
    /*this->fun=other.fun;
    this->funArmy=other.funArmy;*/
    this->buttonFunction=other.buttonFunction;
}

Button &Button::operator=(const Button &other) {
    if(this!=&other){
        delete[] this->name;
        this->id=other.id;
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
      /*  this->fun = other.fun;
        this->funArmy=other.funArmy;*/
        this->buttonFunction=other.buttonFunction;
    }
    return *this;
}

void Button::setId(unsigned const int id) {
    this->id=id;
}

unsigned int Button::getId()const {
    return this->id;
}

const char* Button::getName()const{
    return name;
}

ButtonFunction Button::getFunction()const {
    return this->buttonFunction;
}


