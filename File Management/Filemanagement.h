#ifndef NHF_REFORMED_FILEMANAGEMENT_H
#define NHF_REFORMED_FILEMANAGEMENT_H
#include <fstream>
#include "../List/List.hpp"
#include "../Game/Army.h"
#include "../Game/Piece.h"
#include <vector>
#include <string>
#include <sstream>

class Filemanagement{
public:
    static List<Army> ListofArmies(const char* filename);
    static void AppendArmy(Army* army,const char* filename);
    static void EditArmy(Army* army,const char* filename);
    static void DeleteArmy(Army* army,const char* filename);

private:
    static void readTillLine(std::ifstream& file, std::vector<std::string>& lines,const std::string& boundary="");
    static void skipLines(std::ifstream& file,int numberofLines);
    static void writeLines(std::ofstream& file,std::vector<std::string>& lines);
    static void writeArmy(std::ofstream& file,Army* army);
    static void overwriteline(const char* filename,std::string newLine,int lineNumber);
    static void adjustStringNumber(std::string& string,bool increment);

};
#endif //NHF_REFORMED_FILEMANAGEMENT_H