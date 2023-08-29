#include "Argument.hpp"

argument::argument(
        const char* key,
        argument::type arg_type,
        argument::declaration arg_decl,
        const char* description,
        argument::mode arg_mode,
        const char* default_value
        ) : _key(key), _arg_type(arg_type), _arg_decl(arg_decl), _description(description), _arg_mode(arg_mode)
{
    _decl_amount = 0;
    if (arg_type == argument::type::parameter && arg_mode == argument::mode::required)
    {
        std::string what_msg("Required argument " + std::string(key) + " cannot be used with default value");
        throw std::invalid_argument(what_msg);
    }

    if (arg_type == argument::type::parameter && default_value == nullptr)
    {
        std::string what_msg("Optional argument " + std::string(key) + " cannot be assigned nullptr as default value");
        throw std::invalid_argument(what_msg);
    }
}
