#ifndef NHF_REFORMED_UI_H
#define NHF_REFORMED_UI_H


class ui {
private:

protected:

public:
    ui(){}
    virtual void show()=0;
    virtual bool input()=0;
    virtual void idle()=0;
    void clear();
};


#endif //NHF_REFORMED_UI_H
