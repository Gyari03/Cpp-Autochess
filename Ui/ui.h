#ifndef NHF_REFORMED_UI_H
#define NHF_REFORMED_UI_H

class ui {
public:
    ui(){}
    virtual void display()=0;
    virtual bool handleInput()=0;
    virtual void idle()=0;

    static void clearScreen();
    static void delayMilliseconds(unsigned int ms);
};
#endif //NHF_REFORMED_UI_H
