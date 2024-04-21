#include "Filemanagement.h"

List<Army>* ListofArmies(const char* filename){
    int countofArmies;
    char nameofcurrentArmy[35];
    int sizeofcurrentArmy;

    std::ifstream file(filename);
    if (!file) {
        return nullptr;
    }
    List<Army> *armies = new List<Army>;
    file >> countofArmies;
    for (int i = 0; i < countofArmies; i++) {
        Army *newArmy = new Army;

        file >> nameofcurrentArmy;
        newArmy->setnameofArmy(nameofcurrentArmy);

        file >> sizeofcurrentArmy;
        for (int j = 0; j < sizeofcurrentArmy; j++) {
            char piece_name;
            int piece_x, piece_y;
            file >> piece_name;
            file >> piece_x;
            file >> piece_y;
            newArmy->addPiece(*createPiece(piece_name, piece_x, piece_y));
        }
        armies->addtoList(newArmy);
    }
    return armies;
}

void readTillLine(std::ifstream& file, std::vector<std::string>& lines,const std::string& boundary){ //ha a boundary üres akkor a file legvégéig olvas
    std::string currentLine;
    while(std::getline(file,currentLine)){
        if(currentLine==boundary && !(boundary.empty())){
            break;
        }
        lines.push_back(currentLine);
    }
}
void skipLines(std::ifstream& file,int numberofLines){ //piecesToSkip*3
    if(numberofLines==0){return;}
    std::string currentLine;
    for (int i = 0; i <= numberofLines; ++i) { //azért *3 mivel egy bábu 3 sorból áll
        std::getline(file,currentLine);
    }
}

void writeLines(std::ofstream& file,std::vector<std::string>& lines){
    for(size_t i=0;i<lines.size();++i){
        file<<lines[i];
        file<<std::endl;
    }
}

void writeArmy(std::ofstream& file,Army* army){
    //   file<<std::endl;
    file<<army->getnameofArmy()<<std::endl;
    file<<army->getsizeofArmy()<<std::endl;
    for (int i = 0; i < army->getsizeofArmy(); ++i) {
        file<<army->getPiece(i)->getname()<<std::endl;
        file<<army->getPiece(i)->getcoordX()<<std::endl;
        file<<army->getPiece(i)->getcoordY();
        file<<std::endl;
    }
}


void overwriteline(const char* filename,std::string newLine,int lineNumber){

    std::ifstream readfile(filename);
    if(!readfile){return;}

    std::vector<std::string> lines;
    std::string currentLine;

    while(std::getline(readfile,currentLine)){
        lines.push_back(currentLine);
    }
    readfile.close();

    lines[lineNumber-1]=newLine;

    std::ofstream writefile(filename);
    if(!writefile){return;}

    for(size_t i=0;i<lines.size();++i){
        writefile<<lines[i];
        if(i!=lines.size()-1){
            writefile<<std::endl;
        }
    }
    writefile.close();
}

void adjustStringNumber(std::string& string,bool increment){ //if increment true->increment, false->decrement
    std::istringstream stringstream1(string);
    int number;
    stringstream1>>number;
    if(increment){number++;}
    else{number--;}
    std::ostringstream stringstream2;
    stringstream2<<number;
    string = stringstream2.str();
}

void AppendArmy(Army* army,const char *filename){

    //Előző érték kiolvasása
    std::string countofArmies;
    std::ifstream countofArmies_file(filename);
    if(!countofArmies_file){return;}
    countofArmies_file>>countofArmies;
    countofArmies_file.close();


    //Megnövelése 1-el és beírása
    adjustStringNumber(countofArmies,true);
    overwriteline(filename,countofArmies,1);


    //append to the end of the file
    std::ofstream file(filename,std::ios_base::app);
    if (!file) {
        return;
    }
    file<<std::endl; //std::ios_bas::app nem rak hozzá valamiért új sort... LEHET ÚJRA KELL ÍRNI AZ EGÉSZET
    writeArmy(file,army);
}


//ALGORITMUS LEÍRÁSA
//Beolvassuk a sorokat
//Név alapján kikeressük az armyt-t akikt editelünk
//Kiolvassuk utána, hogy hány bábu van
//Ebből tudjuk, hogy hány sort kell majd ignorálni
//a beolvasás második részét egy 2. stringvectorba tároljuk
//bezárjuk a beolvasást
//írásra megnyitjuk:
//Beleírjuk az első stringvector tartalmát, ami az editelendő armi előtt megáll
//Army* army alapján beleírjuk a fileba
//beleírjuk a második stringvectort a fileba
//KÉSZ
void EditArmy(Army* army,const char* filename){
    std::ifstream readfile(filename);
    if(!readfile){return;}

    std::string name = army->getnameofArmy();
    std::vector<std::string> lines1;//First half
    std::vector<std::string> lines2;//Second half
    std::string currentLine;
    int piecesToSkip;

    readTillLine(readfile,lines1,name);
    readfile>>piecesToSkip;
    skipLines(readfile,piecesToSkip*3);
    currentLine.clear();
    readTillLine(readfile,lines2);
    readfile.close();

    std::ofstream writefile(filename);
    if (!writefile){return;}
    writeLines(writefile,lines1); //lines1 beírása
    writeArmy(writefile,army); //átírt army beírása
    writeLines(writefile,lines2); //lines2 beírása

}


//ALGORITMUS LEÍRÁSA
//overwriteline az elsőt: 1-el csökkentjük
//Megint lesz lines1 és lines2
//lines1 a kitörlendő nevéig megy
//skippeljük az armyt
//lines2 beolvasása
//kiírjuk lines1-et és lines2-őt


void DeleteArmy(Army* army,const char* filename){

    std::ifstream readfile(filename);
    if(!readfile){return;}

    //NumberOfArmies csökkentése
    std::vector<std::string> lines1;
    std::vector<std::string> lines2;
    std::string currentLine;
    int piecesToSkip;

    std::getline(readfile, currentLine);
    readfile.close();
    adjustStringNumber(currentLine,false);
    overwriteline(filename,currentLine,1);

    readfile.open(filename);
    if(!readfile){return;}
    readTillLine(readfile, lines1, army->getnameofArmy());
    readfile >> piecesToSkip;
    skipLines(readfile, piecesToSkip * 3);
    readTillLine(readfile, lines2);
    readfile.close();

    std::ofstream writefile(filename);
    writeLines(writefile,lines1);
    writeLines(writefile,lines2);
}