#ifndef NHF_REFORMED_BUTTON_H
#define NHF_REFORMED_BUTTON_H
#include "../Game/Army.h"
#include "ButtonFunctionHandler.h"

class Button{
private:
    size_t id; //majd a menu szamlalo jelenlegi erteket kapja meg
    char* name; //parameterkent kapott nev
    ButtonFunctionHandler buttonFunction;

public:
    Button();
    Button(const char* name,size_t id,void (*function)());
    Button(const char* name,size_t id,void (*functionArmy)(Army*),Army* armyPtr);
    Button(const char* name,size_t id,void (*functionArmy)(Army* first,Army* second),Army* armyPtr1,Army* armyPtr2);
    ~Button();
    Button(const Button& other);
    Button& operator=(const Button& other);
    void setId(size_t id);
    size_t getId()const;
    const char* getName()const;
    ButtonFunctionHandler getFunction()const;
};
#endif //NHF_REFORMED_BUTTON_H