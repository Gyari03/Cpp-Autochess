#ifndef NHF_REFORMED_BUTTONVOID_H
#define NHF_REFORMED_BUTTONVOID_H
#include "button.h"

class Buttonvoid:public Button {
private:
    void (*function)(); //megnyomaskor aktivalodott fuggveny

public:
    Buttonvoid(const char* name,unsigned int id,void (*function)()):Button(name,id){
        this->function=function;
    }
    void (*getFunction())(){
        return function;
    }
};


#endif //NHF_REFORMED_BUTTONVOID_H
