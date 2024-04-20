#ifndef NHF_REFORMED_UIEDITOR_H
#define NHF_REFORMED_UIEDITOR_H
#include "../Editor/Editor.h"
#include "ui.h"
#include <iostream>
#include "../File Management/Filemanagement.h"


class uiEditor:public ui {
private:
    Editor* editor;

public:
    uiEditor(Editor* editor);
    ~uiEditor();

    void show() override;
    void input() override;//megirni
    void renderTable(); //megirni
    Piece* searchfor(int x,int y){
        return editor->getArmy()->getPiece(x,y);
    }

    void idle()override;
    void saveArmy();
    void saveArmy(Army* army); //már létrehozott army mentése

};

void Run(Editor* editorptr);


#endif //NHF_REFORMED_UIEDITOR_H
