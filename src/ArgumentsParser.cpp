#include "ArgumentsParser.hpp"

// namespace stdfs = std::filesystem;

arguments_parser::arguments_parser(const char* prog_info) : _prog_info(prog_info) {}

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
        argument* arg_p {nullptr};

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

const argument* arguments_parser::operator[](std::string key) const
{
    return _arguments.at(key);
}

const std::vector<argument *> &arguments_parser::recieved_arguments() const
{
    return _recieved_args;
}

// TODO (implement std::filesystem solution)
void arguments_parser::show_help() const
{
    this->help_prefix();

    for (const auto& arg_pair : _arguments)
        arg_pair.second->show_help();
        // show_help(arg_pair.first);
}

void arguments_parser::show_help(std::string key) const
{
    this->help_prefix();
    _arguments.at(key)->show_help();
    // const argument* arg {_arguments.at(key)};
    // std::cout << arg->key();

    // if (arg->arg_mode() == argument::mode::required)
    //     std::cout << "\tREQUIRED";
    // else
    //     std::cout << "\tOPTIONAL";

    // if (arg->arg_type() == argument::type::flag)
    //     std::cout << "\tFLAG";
    // else
    //     std::cout << "\tPARM";

    // if (arg->arg_decl() == argument::declaration::single)
    //     std::cout << "\tSINGLE";
    // else
    //     std::cout << "\tMULTI";

    // std::printf("\t%s\n", arg->description());
}

arguments_parser::~arguments_parser()
{
    for (auto iter = _arguments.begin(); iter != _arguments.end(); iter++)
    {
        delete iter->second;
        _arguments.erase(iter);
    }
}

void arguments_parser::help_prefix() const
{
    std::puts("Usage:");

    char exe_path[PATH_MAX+1];
    readlink("/proc/self/exe", exe_path, PATH_MAX);
    std::printf("%s <FLAGS> <PARAMETERS>\n\n", exe_path);


    // std::cout << fs::weakly_canonical(stdfs::path("/proc/self/exe")) << " <FLAGS> <PARAMETERS>\n\n";
    // std::printf("%s <FLAGS> <PARAMETERS>\n\n", stdfs::read_symlink("/proc/self/exe").c_str());

    std::puts(_prog_info);
    std::puts("----\n");
    std::puts("KEY\tMODE\tTYPE\tDECL\tDESCRIPTION");
}
