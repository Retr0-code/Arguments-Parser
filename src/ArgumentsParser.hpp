#ifndef ARGUMENTS_PARSER_HPP
#define ARGUMENTS_PARSER_HPP

#include <iostream>
#include <unordered_map>

#include "Argument.hpp"
#include "Exceptions.hpp"


class arguments_parser
{
public:
    arguments_parser();

    void add_argument(argument* arg);

    void add_argument(
        const char* key,
        argument::type arg_type,
        argument::declaration arg_decl,
        const char* description,
        argument::mode arg_mode = argument::mode::optional,
        const char* default_value = nullptr
    );

    void parse(int argc, char const** argv);

    const argument& operator[](std::string key);

    ~arguments_parser();

private:
    std::unordered_map<std::string, argument*> _arguments;
    std::unordered_map<argument*, bool> _required_args;
};

#endif
