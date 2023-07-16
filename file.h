#pragma once
#include <filesystem>
#include <fstream>
#include <bitset>
#include <vector>

#include "log.h"
#include "utility/utils.h"

namespace saheki::file
{
    /* IN FILE */

    template <typename _Elem = char, size_t bits = 8>
    _GLIBCXX_NODISCARD std::vector<std::bitset<bits>> input_binary(const std::filesystem::path &file_path) noexcept
    {
        std::basic_ifstream<_Elem> fs;
        fs.open(file_path, std::ios::binary);
        if (fs.is_open())
        {
            std::vector<std::bitset<bits>> data(std::istreambuf_iterator<_Elem>(fs), {});
            if (fs.bad())
            {
                log::fatal("stream is in bad state reading ", file_path);
            }
            return data;
        }
        log::fatal("could not open ", file_path);
        return std::vector<std::bitset<bits>>();
    }

    template <typename _Elem = char>
    _GLIBCXX_NODISCARD std::basic_string<_Elem> input(const std::filesystem::path &file_path) noexcept
    {
        std::basic_ifstream<_Elem> fs;
        fs.open(file_path, std::ios::binary);
        if (fs.is_open())
        {
            std::basic_string<_Elem> data(std::istreambuf_iterator<_Elem>(fs), {});
            if (fs.bad())
            {
                log::fatal("stream is in bad state reading ", file_path);
            }
            return data;
        }
        log::fatal("could not open ", file_path);
        return std::basic_string<_Elem>();
    }

    /* OUT FILE */

    template <typename _Elem = char>
    void output(const std::filesystem::path &file_path, typename std::basic_string<_Elem>::const_iterator begin,
                typename std::basic_string<_Elem>::const_iterator end, const bool &app) noexcept
    {
        std::basic_ofstream<_Elem> fs;
        if (app)
        {
            fs.open(file_path, std::ios::out | std::ios::app);
        }
        else
        {
            fs.open(file_path, std::ios::out);
        }
        if (fs.is_open())
        {
            std::copy(begin, end, std::ostreambuf_iterator<_Elem>(fs));
            if (fs.bad())
            {
                log::fatal("stream is in bad state writing ", file_path);
            }
        }
        else
        {
            log::fatal("could not open ", file_path);
        }
    }

    template <typename _Elem = char>
    void output(const std::filesystem::path &file_path, std::basic_string<_Elem> str, const bool &app) noexcept
    {
        output(file_path, str.begin(), str.end(), app);
    }

    /* UTIL FILE */

    enum class end_line_sequence
    {
        str,
        lf,
        cr,
        crlf
    };

    template <typename char_t = char>
    _GLIBCXX_NODISCARD constexpr end_line_sequence get_end_line_sequence(typename std::basic_string<char_t>::const_iterator begin,
                                                                         typename std::basic_string<char_t>::const_iterator end) noexcept
    {
        using namespace saheki;

        for (auto it = begin; it != end; ++it)
        {
            if (*it == char_t(13)) // '\r'
            {
                if (utils::next_ok<std::basic_string<char_t>>(it, end))
                {
                    if (*(it + 1) == char_t(10)) // '\n'
                    {
                        return end_line_sequence::crlf;
                    }
                }
                return end_line_sequence::cr;
            }
            if (*it == char_t(10)) // '\n'
            {
                return end_line_sequence::lf;
            }
        }
        return end_line_sequence::str;
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD constexpr end_line_sequence get_end_line_sequence(std::basic_string<char_t> &str) noexcept
    {
        return get_end_line_sequence(str.begin(), str.end());
    }

    template <typename char_t = char>
    constexpr void end_line_sequence_convert(std::basic_string<char_t> &str, const end_line_sequence &from, const end_line_sequence &to) noexcept
    {
        log::warnning("end_line_sequence_convert is in development");
        
        // no conversion needed
        if (from == to || from == end_line_sequence::str)
        {
            return;
        }

        // crlf to lf
        for (auto it = str.begin(); it != str.end(); ++it)
        {
            if (*it == '\r')
            {
                str.erase(it);
            }
        }

        // // crlf to cr
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\n')
        //     {
        //         str.erase(it);
        //     }
        // }

        // // cr to lf
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\r')
        //     {
        //         *it = '\n';
        //     }
        // }

        // // lf to cr
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\n')
        //     {
        //         *it = '\r';
        //     }
        // }

        // // lf to crlf
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\n')
        //     {
        //         str.insert(it - 1, '\r');
        //     }
        // }

        // // cr to crlf
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\r')
        //     {
        //         str.insert(it, '\n');
        //     }
        // }

        // // cr to str
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\r')
        //     {
        //         str.erase(it);
        //     }
        // }

        // // lf to str
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\n')
        //     {
        //         str.erase(it);
        //     }
        // }

        // // crlf to str
        // for (auto it = str.begin(); it != str.end(); ++it)
        // {
        //     if (*it == '\r' || *it == '\n')
        //     {
        //         str.erase(it);
        //     }
        // }
    }

    // enum file_encoding
    // {
    //     UTF32,
    //     UTF16,
    //     UTF8_BOM,
    //     UTF8,
    //     ANSI
    // };

} // namespace end
