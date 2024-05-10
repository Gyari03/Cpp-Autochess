#ifndef NHF_REFORMED_ERROR_H
#define NHF_REFORMED_ERROR_H
#include <stdexcept>

class CustomError:public std::exception {
public:
    virtual const char* what() const noexcept{
        return "xddddddd";
    }
};
#endif //NHF_REFORMED_ERROR_H