#ifndef NHF_REFORMED_BUTTON_H
#define NHF_REFORMED_BUTTON_H

#include "../Game/Army.h"


class Button{
private:
    unsigned int id; //majd a menu szamlalo jelenlegi erteket kapja meg
    char* name; //parameterkent kapott nev
    void (*function)(); //megnyomaskor aktivalodott fuggveny
    void (*functionArmy)(Army *army);

public:
    Button();
    Button(const char* name,int id,void (*function)());
    Button(const char* name,unsigned int id,void (*functionArmy)(Army*));
    ~Button();
    Button(const Button& other);
    Button& operator=(const Button& other);
    void setId(unsigned int id);
    unsigned int getId()const;
    const char* getName()const;
    //void (*getFunction())();

    //Button(const char string[5], unsigned int i, void (*pFunction)(Menu &));
};

#endif //NHF_REFORMED_BUTTON_H
