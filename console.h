#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "log.h"

namespace saheki::console
{
    /* In */

    template <typename type, typename char_type>
    _GLIBCXX_NODISCARD constexpr type input(std::basic_istream<char_type> &in = std::cin) noexcept
    {
        log::warnning("input needs revision");
        std::basic_stringstream<char_type> temp_ss;
        {
            char_type temp_char = 0;
            while (true)
            {
                if (in.get(temp_char))
                {
                    if (temp_char == std::use_facet<std::ctype<char_type>>(std::locale()).widen('\n'))
                    {
                        break; // means the end of the input
                    }
                    if(temp_ss.put(temp_char))
                    {
                        exit(1); // bad fail
                    }
                    temp_char = 0;
                }
                else
                {
                    in.clear();
                    return type(); // in or ss got a bad fail
                }
            }
        }
        if ((temp_ss.str()).empty())
        {
            return type(); // is empty
        }
        temp_ss.seekg(-1, std::ios_base::end); // the end -1 of input sequence
        const std::streampos end = temp_ss.tellg();
        temp_ss.seekg(0);
        temp_ss.clear();
        type temp; // this may fail
        if (temp_ss >> temp)
        {
            if (temp_ss.tellg() != end)
            {
                return type(); // multiple entries is a bad input
            }
        }
        else
        {
            return type(); // is an incompatible type
        }
        return temp; // ok
    }

    template <typename char_type>
    _GLIBCXX_NODISCARD constexpr std::basic_string<char_type> input_line(std::basic_istream<char_type> &in = std::cin) noexcept
    {
        log::warnning("input_line needs revision");
        using type = std::basic_string<char_type>;
        std::basic_stringstream<char_type> temp_ss;
        {
            char_type temp_char = 0;
            while (true)
            {
                if (in.get(temp_char))
                {
                    if (temp_char == std::use_facet<std::ctype<char_type>>(std::locale()).widen('\n'))
                    {
                        break; // means the end of the input
                    }
                    if(temp_ss.put(temp_char))
                    {
                        exit(1); // bad fail
                    }
                    temp_char = 0;
                }
                else
                {
                    in.clear();
                    return type(); // in or ss got a bad fail
                }
            }
        }
        if ((temp_ss.str()).empty())
        {
            return type(); // is empty
        }
        return temp_ss.str(); // ok
    }

} // namespace end