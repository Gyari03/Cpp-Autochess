#ifndef NHF_REFORMED_FILEMANAGEMENT_H
#define NHF_REFORMED_FILEMANAGEMENT_H
//#include <iostream>
#include <fstream>
#include "../Game/List.hpp"
#include "../Game/Army.h"
#include "../Game/Piece.h"
#include <vector>
#include <string>
#include <sstream>


//Kiolvasás
List<Army>* ListofArmies(const char* filename);

//Beleírás
void overwriteline(const char* filename,const char* newLine,int lineNumber);

void incrementstringnum(std::string& string);

void AppendArmy(Army* army,const char* filename);


#endif //NHF_REFORMED_FILEMANAGEMENT_H
