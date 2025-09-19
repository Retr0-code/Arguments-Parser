#include "Argument.hpp"
#include "ArgumentsParser.hpp"

int main(int argc, const char** argv)
{
    arguments_parser arg_parser("Simple example program that demonstartes work of arguments parsing library.");
    
    argument_ptr verbose{ new argument(
        "-v",
        argument::type::flag,
        argument::declaration::multiple,
        "Show more detailed output"
    )};

    arg_parser.add_argument(verbose);
    arg_parser.add_argument(
        "-o",
        argument::type::parameter,
        argument::declaration::single,
        "Writes result to specified file",
        argument::mode::required
    );
    arg_parser.add_argument(
        "--help",
        argument::type::help,
        argument::declaration::single,
        "Shows help message"
    );

    try
    {
        arg_parser.parse(argc, argv);
    }
    catch(const unknown_argument& e)
    {
        std::cerr << e.what();
        return -1;
    }
    catch(const required_arguments& e)
    {
        std::cerr << e.what();
        std::cout << "Check manual using <--help> flag\n";
        return -2;
    }
    catch(const usage_message& e)
    {
        if (arg_parser["--help"]->get_value() == nullptr)
            arg_parser.show_help();
        else
            arg_parser.show_help(arg_parser["--help"]->get_value());
        
        return 0;
    }

    // for (auto& i : arg_parser.recieved_arguments())
    //     std::printf("%s value: %s\n", i->key(), i->get_value());
    
    return 0;
}
