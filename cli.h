#pragma once
#include <functional>
#include <vector>
#include <string>
#include <sstream>

#include "log.h"

namespace saheki
{
    template <typename char_t = char>
    class command
    {
    private: // type
        using string_t = std::basic_string<char_t>;

    public: // data
        std::string name;
        std::vector<std::string> argument;
        size_t parameters;
        std::string help;
        std::function<void()> fn;

    public: // constructor
        constexpr command()
            : name(),
              argument(),
              parameters(),
              help(),
              fn() {}
    };

    class cli
    {
    private: // type
        using char_t = char;
        using string_t = std::basic_string<char_t>;

    public: // data
        std::vector<command<char_t>> commands;

    public: // constructor
        constexpr cli() : commands() {}
    };

} // namespace end
