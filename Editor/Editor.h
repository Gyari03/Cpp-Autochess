#ifndef NHF_REFORMED_EDITOR_H
#define NHF_REFORMED_EDITOR_H
#include "../Game/Army.h"
#include <sstream>
#include <string>

class Editor {
private:
    Army* army;
    bool exit;
    bool toDelete;

public:
    Editor();//Új army készítése
    Editor(Army* army);//Meglévő szerkesztése
    Army* getArmy();
    void updateExit();
    bool getExit()const;
    void updateDelete();
    bool getDelete()const;
};


#endif //NHF_REFORMED_EDITOR_H
