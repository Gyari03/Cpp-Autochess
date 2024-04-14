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

void incrementstringnum(std::string& string){
    std::istringstream stringstream1(string);
    int number;
    stringstream1>>number;
    number++;
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
    incrementstringnum(countofArmies);
    overwriteline(filename,countofArmies,1);


    //append to the end of the file
    std::ofstream file(filename,std::ios_base::app);
    if (!file) {
        return;
    }
    file<<std::endl; //next line for the new content to start
    file<<army->getnameofArmy()<<std::endl;
    file<<army->getsizeofArmy()<<std::endl;
    for (int i = 0; i < army->getsizeofArmy(); ++i) {
        file<<army->getPiece(i)->getname()<<std::endl;
        file<<army->getPiece(i)->getcoordX()<<std::endl;
        file<<army->getPiece(i)->getcoordY();
        if(i!=army->getsizeofArmy()-1){file<<std::endl;}//legutolsó után nem akarunk új sort
    }
}