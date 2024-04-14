#include "ui.h"
#include <cstdlib>

ui::ui():color(White){}

void ui::clear(){
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}