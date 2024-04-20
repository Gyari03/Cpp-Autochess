#ifndef NHF_REFORMED_BUTTON_H
#define NHF_REFORMED_BUTTON_H

#include "../Game/Army.h"


//új class a functionoknek
class ButtonFunction{
private:
    void (*function)(); //megnyomaskor aktivalodott fuggveny
    void (*functionArmy)(Army *army); //Army editelésre használt fv.
    Army* armyPointer;

public:
    ButtonFunction():function(nullptr),functionArmy(nullptr),armyPointer(nullptr){}
    ButtonFunction(void (*func)()):function(func),functionArmy(nullptr),armyPointer(nullptr){}
    ButtonFunction(void (*funcArmy)(Army*),Army* armyPtr):function(nullptr),functionArmy(funcArmy),armyPointer(armyPtr){}
    void execute();

};


class Button{
private:
    unsigned int id; //majd a menu szamlalo jelenlegi erteket kapja meg
    char* name; //parameterkent kapott nev
    /*void (*function)(); //megnyomaskor aktivalodott fuggveny
    void (*functionArmy)(Army *army);*/
    ButtonFunction buttonFunction;

public:
    Button();
    Button(const char* name,int id,void (*function)());
    Button(const char* name,unsigned int id,void (*functionArmy)(Army*),Army* armyPtr);
    ~Button();
    Button(const Button& other);
    Button& operator=(const Button& other);
    void setId(unsigned int id);
    unsigned int getId()const;
    const char* getName()const;
   // void (*getFunction())();
    ButtonFunction getFunction();

};

#endif //NHF_REFORMED_BUTTON_H
