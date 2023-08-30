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
    if (arg_type == argument::type::parameter)
    {
        if (arg_mode == argument::mode::required && default_value != nullptr)
        {
            std::string what_msg("Required argument " + std::string(key) + " cannot be used with default value");
            throw std::invalid_argument(what_msg);
        }

        if (arg_mode == argument::mode::optional && default_value == nullptr)
        {
            std::string what_msg("Optional argument " + std::string(key) + " cannot be assigned nullptr as default value");
            throw std::invalid_argument(what_msg);
        }
    }

    _value = default_value;
}

const char* argument::key() const noexcept
{
    return _key;
}

argument::type argument::arg_type() const noexcept
{
    return _arg_type;
}

argument::declaration argument::arg_decl() const noexcept
{
    return _arg_decl;
}

const char* argument::description() const noexcept
{
    return _description;
}

argument::mode argument::arg_mode() const noexcept
{
    return _arg_mode;
}

uint16_t& argument::decl_amount() noexcept
{
    return _decl_amount;
}

void argument::set_value(const char* value) noexcept
{
    _value = value;
}

void argument::add_value(const char* value)
{
    _value = value;
    _values.push_back(value);
}

const char* argument::get_value() const
{
    return _value;
}

const std::vector<const char *> &argument::get_values() const
{
    return _values;
}
