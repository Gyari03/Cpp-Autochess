#ifndef NHF_REFORMED_UI_H
#define NHF_REFORMED_UI_H

enum Color{White,Red,Green,Blue};

class ui {
private:
    Color color;

protected:

public:
    ui();
    virtual void show()=0;
    virtual void input()=0;
    virtual void idle()=0;
    void clear();
    //virtual void renderTable()=0;

};


#endif //NHF_REFORMED_UI_H
