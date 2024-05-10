#ifndef NHF_REFORMED_BUTTONFUNCTIONHANDLER_H
#define NHF_REFORMED_BUTTONFUNCTIONHANDLER_H

class Army;

class ButtonFunctionHandler{
private:
    void (*fun)(); //megnyomaskor aktivalodott fuggveny
    void (*funArmy)(Army *army); //Army editelésre használt fv.
    void (*funArmyFor2)(Army* army1, Army* army2);
    Army* regArmy1;
    Army* regArmy2;

public:
    ~ButtonFunctionHandler(){}
    ButtonFunctionHandler(): fun(nullptr), funArmy(nullptr), funArmyFor2(nullptr) , regArmy1(nullptr), regArmy2(nullptr){}
    ButtonFunctionHandler(void (*func)()): fun(func), funArmy(nullptr), funArmyFor2(nullptr) , regArmy1(nullptr), regArmy2(nullptr){}
    ButtonFunctionHandler(void (*funcArmy)(Army*), Army* armyPtr): fun(nullptr), funArmy(funcArmy), funArmyFor2(nullptr) , regArmy1(armyPtr), regArmy2(nullptr){}
    ButtonFunctionHandler(void (*funcArmy)(Army*, Army*), Army* armyPtr1, Army* armyPtr2): fun(nullptr), funArmy(nullptr), funArmyFor2(funcArmy), regArmy1(armyPtr1), regArmy2(armyPtr2){}
    void execute();
};
#endif //NHF_REFORMED_BUTTONFUNCTIONHANDLER_H