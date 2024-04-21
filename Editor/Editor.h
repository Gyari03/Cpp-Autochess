#ifndef NHF_REFORMED_EDITOR_H
#define NHF_REFORMED_EDITOR_H
#include "../Game/Army.h"
#include "../File Management/Filemanagement.h"
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
    Piece* searchfor(int x,int y);
    void updateExit();
    bool getExit()const;
    void updateDelete();
    bool getDelete()const;
    void saveArmy(); //új army mentése
    void editArmy(); //már létrehozott army mentése
};


#endif //NHF_REFORMED_EDITOR_H
