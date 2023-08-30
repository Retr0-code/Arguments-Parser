#ifndef ARGUMENTS_PARSER_HPP
#define ARGUMENTS_PARSER_HPP

#include <iostream>
// #include <filesystem>
#include <unordered_map>

#include <unistd.h>
#include <linux/limits.h>

#include "Argument.hpp"
#include "Exceptions.hpp"


class arguments_parser
{
public:
    arguments_parser(const char* prog_info);

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

    const argument* operator[](std::string key) const;

    const std::vector<argument*>& recieved_arguments() const;

    void show_help() const;

    void show_help(std::string key) const;

    ~arguments_parser();

private:
    void help_prefix() const;

private:
    const char* _prog_info;
    std::unordered_map<std::string, argument*> _arguments;
    std::unordered_map<argument*, bool> _required_args;
    std::vector<argument*> _recieved_args;
};

#endif
