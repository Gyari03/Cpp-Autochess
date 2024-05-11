#include "uiEditor.h"
#include "../Editor/Editor.h"
#include "../Exception/Error.h"

#include "../Memtrace/memtrace.h"

uiEditor::uiEditor(Editor *editor):editor(editor) {}

uiEditor::~uiEditor() {
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
                for(int j=0;j<8;j++){ //destinationX+1 és 8-destinationY a konvertálandóak
                    if(editor->searchFor(j+1,8-y)!=nullptr){
                        std::cout << "    " << editor->searchFor(j + 1, 8 - y)->getName() << "    #";
                    }
                    else if(editor->searchFor(j+1,8-y)==nullptr){
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

void uiEditor::display(){
    clearScreen();
    renderTable();
}

bool uiEditor::handleInput(){
    char name;
    int x,y;
    std::string input;

    std::cin>>input;
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
        }catch(const std::exception& e){std::cout << "Error:" << e.what() <<std::endl;}
    }
}

void uiEditor::saveSequence() { //az inputot egyszerre használjuk a névre és a Y/N választásra
    char input[36];

    do{
        clearScreen();
        std::cout<<"Would you like to save this army?(Y/N)"<<std::endl;
        std::cin>>input;
    }
    while(!strchr("YN",toupper(input[0])));


    if(input[0]=='Y'||input[0]=='y'){
        clearScreen();
        bool noErrorsOccurred = false;

        std::cout<<"Give a name to this army: ";
        while(!noErrorsOccurred){
            try{
                std::cin>>input;
                if(isdigit(input[0])){throw Error("Number as first character of army name is forbidden");}
                editor->getArmy()->setnameofArmy(input);
                editor->saveArmy();
                noErrorsOccurred=true;       //Ha throw történik ez nem fut le.
            }catch(const std::exception& e){std::cout << "Error:" << e.what() <<std::endl;}
        }
    }
}

void uiEditor::Run(Editor* editorptr){
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

