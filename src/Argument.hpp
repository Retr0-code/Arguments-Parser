#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <exception>

class argument
{
public:

    enum type : uint8_t
    {
        flag,
        parameter
    };

    enum declaration : uint8_t
    {
        single,
        multiple
    };

    enum mode : uint8_t
    {
        required,
        optional
    };


    argument(const argument&) = delete;

    argument(const argument&&) = delete;

    argument operator=(const argument&) = delete;

    argument operator=(const argument&&) = delete;


    argument(
        const char* key,
        argument::type arg_type,
        argument::declaration arg_decl,
        const char* description,
        argument::mode arg_mode = argument::mode::optional,
        const char* default_value = nullptr
    );

    const char* key() const noexcept;

    argument::type arg_type() const noexcept;

    argument::declaration arg_decl() const noexcept;

    const char* description() const noexcept;

    argument::mode arg_mode() const noexcept;

    uint16_t& decl_amount() noexcept;

    void set_value(const char* value) noexcept;

    void add_value(const char* value);

private:
    const char* _key;
    argument::type _arg_type;
    argument::declaration _arg_decl;
    const char* _description;
    argument::mode _arg_mode;
    uint16_t _decl_amount;
    const char* _value;
    std::vector<const char*> _values;
};

#endif
