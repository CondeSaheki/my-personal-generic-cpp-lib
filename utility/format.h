#pragma once
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <bitset>

namespace saheki::format
{
    template <typename _elem, typename type>
    _GLIBCXX_NODISCARD constexpr std::basic_string<_elem> vector(const std::vector<type> &vec, const std::basic_string<_elem> &separator) noexcept
    {
        if (vec.empty())
        {
            return std::basic_string<_elem>();
        }
        std::basic_stringstream<_elem> ss;
        for (auto it = vec.begin(); it != vec.end() - 1; ++it)
        {
            ss << *it << separator;
        }
        ss << *(vec.end() - 1);
        return ss.str();
    }

    template <typename _elem = char>
    _GLIBCXX_NODISCARD constexpr std::basic_string<_elem> hex(const std::vector<std::bitset<8>> &bin) noexcept
    {
        log::warnning("hex_string is in development");

        if (bin.empty())
        {
            return std::basic_string<_elem>();
        }
        std::basic_stringstream<_elem> ss;
        for (auto it = bin.begin(); it != bin.end() - 1; ++it)
        {
            if (it->to_ulong() <= 15)
            {
                ss << std::hex << std::setw(1) << _elem(48) << it->to_ulong() << _elem(32);
                continue;
            }
            ss << std::hex << std::setw(2) << it->to_ulong() << _elem(32);
        }
        if ((bin.end() - 1)->to_ulong() <= 15)
        {
            ss << std::hex << std::setw(1) << _elem(48) << (bin.end() - 1)->to_ulong();
        }
        else
        {
            ss << std::hex << std::setw(2) << (bin.end() - 1)->to_ulong();
        }
        return ss.str();
    }

    template <size_t decimals, typename num, typename char_t = char>
    constexpr void number(std::basic_stringstream<char_t> &ss, const num &val) noexcept
    {
        auto size = val ? std::floor(std::log10(val) + 1) : 1;
        if (decimals == size)
        {
            ss << val;
        }
        else
        {
            if (decimals > size)
            {
                for (auto it = size; it != decimals; ++it)
                {
                    ss << 0;
                }
                ss << val;
            }
            else
            {
                ss << static_cast<num>(val / powl(10, size - decimals));
            }
        }
    }

    template <size_t decimals, typename num, typename char_t = char>
    _GLIBCXX_NODISCARD constexpr std::basic_string<char_t> number(const num &val) noexcept
    {
        std::basic_stringstream<char_t> ss;
        number(ss, val);
        return ss.str();
    }

} // namespace end