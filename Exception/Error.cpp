#include "Error.h"

Error::Error(std::string& message):message(message){}

const char* Error::what() const noexcept{return message.c_str();}