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
    using arguments_vector = std::vector<argument_ptr>;

    arguments_parser(const char* prog_info);

    void add_argument(argument_ptr arg);

    void add_argument(
        const char* key,
        argument::type arg_type,
        argument::declaration arg_decl,
        const char* description,
        argument::mode arg_mode = argument::mode::optional,
        const char* default_value = nullptr
    );

    void parse(int argc, const char** argv);

    const argument_ptr& operator[](std::string key) const;

    const arguments_vector& recieved_arguments() const;

    void show_help() const;

    void show_help(std::string key) const;

    ~arguments_parser() = default;

private:
    void help_prefix() const;

private:
    std::unordered_map<std::string, argument_ptr> _arguments;
    std::unordered_map<argument_ptr, bool> _required_args;
    arguments_vector _recieved_args;
    const char* _prog_info;
};

#endif
