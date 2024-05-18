#include "ui.h"
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//#define CPORTA

void ui::clearScreen(){
#ifdef CPORTA
   // return; //Ha tesztekkel dolgozunk akkor hagyjuk ki a képenyő tisztítását mert sír a jporta a system hívásoktól
#elif _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ui::delayMilliseconds(unsigned int ms) {
#ifdef CPORTA
    // Ha tesztekkel vagyunk nem kell várakozni
#elif _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}