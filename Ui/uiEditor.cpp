#include "uiEditor.h"
#include "../Editor/Editor.h"

uiEditor::uiEditor(Editor *editor):editor(editor) {}

uiEditor::~uiEditor() {
    delete editor;
}

void uiEditor::renderTable(){
    for(int i=0;i<8;i++){
        if(i!=0){
            std::cout<<"         "<<i+1;
        }
        else{
            std::cout<<"     "<<i+1;
        }
    }
    std::cout<<std::endl;
    for(int y=0;y<8;y++){
        if(y<4 ){
            continue;
        }
        for(int i=0;i<4;i++){
            std::cout<<"#";
            if(i%4==0){
                for(int j=0;j<8;j++){
                    std::cout<<" # # # # #";
                }
                std::cout<<std::endl;
            }
            else if(i%4==1 || i%4==3){
                for(int j=0;j<8;j++){
                    std::cout<<"         #";
                }
                std::cout<<std::endl;
            }
            else if(i%4==2){
                for(int j=0;j<8;j++){ //x+1 és 8-y a konvertálandóak
                    if(editor->searchfor(j+1,8-y)!=nullptr){
                        std::cout<<"    "<<editor->searchfor(j+1,8-y)->getname()<<"    #";
                    }
                    else if(editor->searchfor(j+1,8-y)==nullptr){
                        std::cout<<"         #";
                    }

                    if(j==7){ //Y koordináta számozás
                        std::cout<<"  "<<8-y;
                    }
                }
                std::cout<<std::endl;
            }
        }
        if(y==7){
            std::cout<<"#";
            for(int j=0;j<8;j++){
                std::cout<<" # # # # #";
            }
        }
    }
    std::cout<<std::endl;
}

void uiEditor::show(){
    clear();
    renderTable();
}

bool uiEditor::input(){

    char name;
    int x,y;

    std::string input;
    std::cin>>input;
    name = input[0];
    if(name=='0'){editor->updateExit();return true;}//kilépés
    x = input.substr(1, 1)[0] - '0';
    y = input.substr(2, 1)[0] - '0';
    if(name=='d'|| name=='D'){
        if(input=="delete") {
            editor->updateExit();
            editor->updateDelete();
            editor->deleteArmy();
            return true;
        }
        this->editor->getArmy()->deletePiece(x,y);
        return true;
    }
    this->editor->getArmy()->addPiece(*createPiece(name,x,y));
    return true;
}

void uiEditor::idle(){
    while(!(editor->getExit())){
        show();
        input();
    }
}

void uiEditor::saveSequence() { //az inputot egyszerre használjuk a névre és a Y/N választásra
    clear();
    char input[35];
    std::cout<<"Would you like to save this army?(Y/N)"<<std::endl;
    std::cin>>input;
    if(input[0]=='Y'||input[0]=='y'){
        clear();
        std::cout<<"Give a name to this army: ";
        std::cin>>input;
        editor->getArmy()->setnameofArmy(input);
        //AppendArmy(editor->getArmy(),"armies.txt");
        editor->saveArmy();
    }
}

void Run(Editor* editorptr){
    bool newlymade = false;
    if(strcmp(editorptr->getArmy()->getnameofArmy(),"")==0){ //az alapján hogy a név üres ellenőrizzük, hogy új-e a sereg
        newlymade = true;
    }
    uiEditor editor(editorptr);
    editor.idle();
    if(newlymade){
        editor.saveSequence();
    return;
    }
    else if(!(editorptr->getDelete())){ //ha nem lett elrendelve, hogy töröljék akkor mentsük le a .txt-be:
        editorptr->editArmy();
    }
}

