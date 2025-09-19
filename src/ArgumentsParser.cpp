#include "ArgumentsParser.hpp"

// namespace stdfs = std::filesystem;

arguments_parser::arguments_parser(const char* prog_info) : _prog_info(prog_info) {}

void arguments_parser::add_argument(argument_ptr arg)
{
    _arguments.emplace(std::make_pair(
        std::string(arg->key()),
        arg
    ));

    if (arg->arg_mode() == argument::mode::required)
        _required_args.emplace(std::make_pair(arg, true));
}

void arguments_parser::add_argument(
    const char* key,
    argument::type arg_type,
    argument::declaration arg_decl,
    const char* description,
    argument::mode arg_mode,
    const char* default_value
)
{
    this->add_argument(std::make_shared<argument>(
        key,
        arg_type,
        arg_decl,
        description,
        arg_mode,
        default_value
    ));
}

void arguments_parser::parse(int argc, const char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        argument_ptr arg_p {nullptr};

        try
        {
            arg_p = _arguments.at(argv[i]);
        }
        catch(const std::exception& e)
        {
            throw unknown_argument(argv[i]);
        }

        if (arg_p->arg_type() == argument::type::help)
        {
            arg_p->set_value(argv[++i]);
            throw usage_message();
        }

        if (arg_p->arg_type() == argument::type::parameter)
        {
            if (arg_p->arg_decl() == argument::declaration::single)
                arg_p->set_value(argv[++i]);

            if (arg_p->arg_decl() == argument::declaration::multiple)
                arg_p->add_value(argv[++i]);
        }

        if (arg_p->arg_type() == argument::type::flag)
            arg_p->decl_amount()++ ;

        _required_args[arg_p] = false;
        _recieved_args.push_back(arg_p);
    }

    bool complete_form {true};
    for (auto& req_arg : _required_args)
    {
        if (req_arg.second)
        {
            std::printf("Argument <%s> is required\n", req_arg.first->key());
            complete_form = false;
        }
    }
    
    if (!complete_form)
        throw required_arguments();
}

const argument_ptr& arguments_parser::operator[](std::string key) const
{
    return _arguments.at(key);
}

const arguments_parser::arguments_vector &arguments_parser::recieved_arguments() const
{
    return _recieved_args;
}

void arguments_parser::show_help() const
{
    this->help_prefix();

    for (const auto& arg_pair : _arguments)
        arg_pair.second->show_help();
}

void arguments_parser::show_help(std::string key) const
{
    this->help_prefix();
    _arguments.at(key)->show_help();
}

void arguments_parser::help_prefix() const
{
    std::puts("Usage:");

    std::puts(_prog_info);
    std::puts("----\n");
    std::puts("KEY\tMODE\tTYPE\tDECL\tDESCRIPTION");
}
