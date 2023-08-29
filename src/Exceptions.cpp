#include "Exceptions.hpp"

unknown_argument::unknown_argument(const char *key) : _key(key)
{
    std::ostringstream error_stream;
    error_stream << "Unknown parameter <" << _key << ">\n";

    std::string mid_buffer {error_stream.str()};
    size_t msg_len {mid_buffer.length()};
    
    _msg = new char[msg_len];
    strncpy(_msg, mid_buffer.c_str(), msg_len);   
}

unknown_argument::~unknown_argument()
{
    delete _msg;
}

const char* unknown_argument::what() const noexcept
{
    return _msg;
}


const char *required_arguments::what() const noexcept
{
    return "Complete required arguments in order to run program\n";
}
