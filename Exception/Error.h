#ifndef NHF_REFORMED_ERROR_H
#define NHF_REFORMED_ERROR_H
#include <stdexcept>

class Error:public std::exception {
private:
    std::string message;
public:
    Error(std::string message):message(message){}
    const char* what() const noexcept{
        return message.c_str();
    }
};
#endif //NHF_REFORMED_ERROR_H