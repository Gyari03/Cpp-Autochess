#include "uiEditor.h"
#include "../Editor/Editor.h"
#include "../Exception/Error.h"

#include "../Memtrace/memtrace.h"

uiEditor::uiEditor(Editor *editor,std::ostream& os,std::istream& is):ui(os,is),editor(editor) {}

uiEditor::~uiEditor() {
}

void uiEditor::renderTable(){
    for(int i=0;i<8;i++){
        if(i!=0){
            os<<"         "<<i+1;
        }
        else{
            os<<"     "<<i+1;
        }
    }
    os<<std::endl;
    for(int y=0;y<8;y++){
        if(y<4 ){
            continue;
        }
        for(int i=0;i<4;i++){
            os<<"#";
            if(i%4==0){
                for(int j=0;j<8;j++){
                    os<<" # # # # #";
                }
                os<<std::endl;
            }
            else if(i%4==1 || i%4==3){
                for(int j=0;j<8;j++){
                    os<<"         #";
                }
                os<<std::endl;
            }
            else if(i%4==2){
                for(int j=0;j<8;j++){ //destinationX+1 és 8-destinationY a konvertálandóak
                    if(editor->searchFor(j+1,8-y)!=nullptr){
                        os << "    " << editor->searchFor(j + 1, 8 - y)->getName() << "    #";
                    }
                    else if(editor->searchFor(j+1,8-y)==nullptr){
                        os<<"         #";
                    }

                    if(j==7){ //Y koordináta számozás
                        os<<"  "<<8-y;
                    }
                }
                os<<std::endl;
            }
        }
        if(y==7){
            os<<"#";
            for(int j=0;j<8;j++){
                os<<" # # # # #";
            }
        }
    }
    os<<std::endl;
}

void uiEditor::display(){
    clearScreen();
    renderTable();
}

bool uiEditor::handleInput(){
    char name;
    int x,y;
    std::string input;

    is>>input;
    name = input[0];

    if (!strchr("KBQHPROD0", toupper(name))) {throw Error("Invalid first character input");} //hibakezelés

    if(name=='0'){editor->updateExit();return true;}//kilépés
    x = input[1] - '0';
    y = input[2] - '0';
    if(strchr("09",input[1]) || strchr("09",input[2])){throw Error("Invalid X-Y coordinate input");} //hibakezelés
    if(name=='d'|| name=='D'){
        if(input=="delete") {
            if(strcmp(editor->getArmy()->getnameofArmy(),"")==0){throw Error("Cannot delete non-existent army");} //hibakezelés
            editor->updateExit();
            editor->updateDelete();
            editor->deleteArmy();
            return true;
        }
        this->editor->getArmy()->deletePiece(x,y);
        return true;
    }
    this->editor->getArmy()->addPiece(*Piece::createPiece(name,x,y));
    return true;
}

void uiEditor::idle(){
    display();
    while(!(editor->getExit())){
        try{
            handleInput();
            display();
        }catch(const std::exception& e){os << "Error:" << e.what() <<std::endl;}
    }
}

void uiEditor::saveSequence() { //az inputot egyszerre használjuk a névre és a Y/N választásra
    char input[36];

    do{
        clearScreen();
        os<<"Would you like to save this army?(Y/N)"<<std::endl;
        is>>input;
    }
    while(!strchr("YN",toupper(input[0])));


    if(input[0]=='Y'||input[0]=='y'){
        clearScreen();
        bool noErrorsOccurred = false;

        os<<"Give a name to this army: ";
        while(!noErrorsOccurred){
            try{
                is>>input;
                if(isdigit(input[0])){throw Error("Number as first character of army name is forbidden");}
                editor->getArmy()->setnameofArmy(input);
                editor->saveArmy();
                noErrorsOccurred=true;       //Ha throw történik ez nem fut le.
            }catch(const std::exception& e){os << "Error:" << e.what() <<std::endl;}
        }
    }
}

void uiEditor::Run(Editor* editorptr,std::ostream& os,std::istream& is){
    bool newlymade = false;
    if(strcmp(editorptr->getArmy()->getnameofArmy(),"")==0){ //az alapján hogy a név üres ellenőrizzük, hogy új-e a sereg
        newlymade = true;
    }
    uiEditor editor(editorptr,os,is);
    editor.idle();
    if(newlymade){
        editor.saveSequence();
    return;
    }
    else if(!(editorptr->getDelete())){ //ha nem lett elrendelve, hogy töröljék akkor mentsük le a .txt-be:
        editorptr->editArmy();
    }
}
