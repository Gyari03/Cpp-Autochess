#ifndef NHF_REFORMED_BUTTONFUNCTION_H
#define NHF_REFORMED_BUTTONFUNCTION_H

class Army;

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


#endif //NHF_REFORMED_BUTTONFUNCTION_H
