#include "ui.h"
#include <cstdlib>

void ui::clear(){
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}