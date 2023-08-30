#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <exception>

class unknown_argument : public std::exception
{
public:
    unknown_argument(const char* key);

    ~unknown_argument();

    const char* what() const noexcept override;

private:
    const char* _key;
    char* _msg;
};


class required_arguments : public std::exception
{
public:
    required_arguments() = default;

    const char* what() const noexcept override;
};


class usage_message : public std::exception
{
public:
    usage_message() = default;

    const char* what() const noexcept override;
};

#endif
