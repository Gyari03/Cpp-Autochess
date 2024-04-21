#ifndef NHF_REFORMED_FILEMANAGEMENT_H
#define NHF_REFORMED_FILEMANAGEMENT_H
//#include <iostream>
#include <fstream>
#include "../List/List.hpp"
#include "../Game/Army.h"
#include "../Game/Piece.h"
#include <vector>
#include <string>
#include <sstream>


//Kiolvasás
List<Army>* ListofArmies(const char* filename);

void readTillLine(std::ifstream& file, std::vector<std::string>& lines,const std::string& boundary="");

void skipLines(std::ifstream& file,int numberofLines);//skip n lines


//Beleírás
void writeLines(std::ofstream& file,std::vector<std::string>& lines);

void writeArmy(std::ofstream& file,Army* army);

void overwriteline(const char* filename,std::string newLine,int lineNumber);

void adjustStringNumber(std::string& string,bool increment);

void AppendArmy(Army* army,const char* filename);

void EditArmy(Army* army,const char* filename);

void DeleteArmy(Army* army,const char* filename);


#endif //NHF_REFORMED_FILEMANAGEMENT_H
