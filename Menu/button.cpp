#include "button.h"
#include <cstring>

#include "../Memtrace/memtrace.h"

Button::Button():id(0),name(nullptr),buttonFunction(std::cout,std::cin){}

Button::Button(const char* name,size_t id,void (*function)(std::ostream& ostream,std::istream& istream),std::ostream& os,std::istream& is):id(id),buttonFunction(function,os,is) {
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}

Button::Button(const char *name, size_t id, void (*functionArmy)(Army* army,std::ostream& ostream,std::istream& istream),Army* armyPtr,std::ostream& os,std::istream& is):buttonFunction(functionArmy,armyPtr,os,is) {
    this->id=id;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}

Button::Button(const char *name, size_t id, void (*functionArmy)(Army* first, Army* second,std::ostream& ostream,std::istream& istream), Army *armyPtr1,Army* armyPtr2,std::ostream& os,std::istream& is): buttonFunction(functionArmy,armyPtr1,armyPtr2,os,is) {
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

void Button::setId(size_t idx) {
    this->id=idx;
}

size_t Button::getId()const {
    return this->id;
}

const char* Button::getName()const{
    return name;
}

ButtonFunctionHandler Button::getFunction()const {
    return this->buttonFunction;
}


