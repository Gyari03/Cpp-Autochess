#include "ui.h"
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void ui::clearScreen(){
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ui::delayMilliseconds(unsigned int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}