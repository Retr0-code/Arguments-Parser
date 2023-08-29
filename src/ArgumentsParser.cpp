#include "ArgumentsParser.hpp"


arguments_parser::arguments_parser()
{

}

void arguments_parser::add_argument(argument* arg)
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
    argument* arg = new argument(
        key,
        arg_type,
        arg_decl,
        description,
        arg_mode,
        default_value
    );

    this->add_argument(arg);
}

void arguments_parser::parse(int argc, char const **argv)
{
    for (int i = 1; i < argc; i++)
    {
        try
        {
            argument* arg_p {_arguments.at(argv[i])};

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
        }
        catch(const std::exception& e)
        {
            throw unknown_argument(argv[i]);
        }
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

    // for (auto& i : _arguments)
    // {
    //     std::printf("%s:\n\t%s\n\t%i\n---\n", i.first.c_str(), i.second->key(), i.second->decl_amount());
    // }
}

arguments_parser::~arguments_parser()
{
    for (auto iter = _arguments.begin(); iter != _arguments.end(); iter++)
    {
        delete iter->second;
        _arguments.erase(iter);
    }
}