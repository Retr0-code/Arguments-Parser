#include "Argument.hpp"
#include "ArgumentsParser.hpp"

int main(int argc, char const *argv[])
{
    arguments_parser arg_parser;
    argument verbose(
        "-v",
        argument::type::flag,
        argument::declaration::multiple,
        "Show more detailed output"
        );

    arg_parser.add_argument(verbose);
    arg_parser.add_argument(
        "-o",
        argument::type::parameter,
        argument::declaration::single,
        "Writes result to file"
    );

    return 0;
}
