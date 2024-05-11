/**
 * @file error.h
 * @brief Az error osztály deklarációit tartalmazza.
 */

#ifndef NHF_REFORMED_ERROR_H
#define NHF_REFORMED_ERROR_H
#include <stdexcept>


/**
 * @brief Saját error osztály.
 * Az osztály az std::exception-ből származik és külön hibaüzenetet produkál.
 */
class Error:public std::exception {

private:
    std::string message; /**< The error message. */
    
public:
    /**
     * @brief Error objektumnak a konstruktora adott hibaüzenettel.
     * @param message Hibaüzenet.
     */
    Error(std::string& message);


    /**
     * @brief Visszatér egy C típusú sztringgel, ami leírja a hiba típusát.
     * @return Hibaüzenet.
     */
    const char* what() const noexcept;
};
#endif //NHF_REFORMED_ERROR_H