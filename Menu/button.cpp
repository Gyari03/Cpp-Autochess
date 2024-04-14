#include "button.h"
#include <cstring>

Button::Button():id(0),name(nullptr),function(nullptr){}

Button::Button(const char* name,unsigned int id) {
    this->id=id;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);

}

/*
Button::Button(const char *name, unsigned int id, void (*function)(Army* army)) {
    this->id=id;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    this->function=function;
}
*/

Button::~Button() {
    delete[] name;
}

Button::Button(const Button &other) {
    this->id=other.id;
    this->name=new char[strlen(other.name)+1];
    strcpy(this->name,other.name);
    this->function=other.function;
}

Button &Button::operator=(const Button &other) {
    if(this!=&other){
        delete[] this->name;
        this->id=other.id;
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->function = other.function;
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
/*
void (*Button::getFunction())(){
    return function;
}
*/