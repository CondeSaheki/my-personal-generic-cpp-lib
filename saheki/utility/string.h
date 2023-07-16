#pragma once
#include <vector>
#include <string>

#include "utils.h"

namespace saheki::string
{
    template <typename char_t = char>
    _GLIBCXX_NODISCARD std::vector<std::basic_string<char_t>> split(typename std::basic_string<char_t>::const_iterator begin,
                                                                    typename std::basic_string<char_t>::const_iterator end,
                                                                    const char_t &character) noexcept
    {
        std::vector<std::basic_string<char_t>> splits;
        auto pos = begin;
        for (auto it = begin; it != end; ++it)
        {
            if (*it == character)
            {
                if (std::distance(pos, it) != 0)
                {
                    splits.emplace_back(pos, it);
                }
                pos = it + 1;
            }
        }
        if (std::distance(pos, end) != 0)
        {
            splits.emplace_back(pos, end);
        }
        return splits;
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD std::vector<std::basic_string<char_t>> split(const std::basic_string<char_t> &str, const char_t &character) noexcept
    {
        return split(str.begin(), str.end(), character);
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD std::vector<std::basic_string<char_t>> split(typename std::basic_string<char_t>::const_iterator begin,
                                                                    typename std::basic_string<char_t>::const_iterator end,
                                                                    const std::basic_string<char_t> &str) noexcept
    {
        std::vector<std::basic_string<char_t>> splits;
        auto pos = begin;
        bool match = true;
        for (auto it = begin; it != end; ++it)
        {
            if ((*it == *str.begin()) && utils::next_ok<std::basic_string<char_t>>(it, end))
            {
                match = true;
                for (auto ita = it + 1, itb = str.begin() + 1; ita != end && itb != str.end(); ++ita, ++itb)
                {
                    if (*ita != *itb)
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    if (std::distance(pos, it) != 0)
                    {
                        splits.emplace_back(pos, it);
                    }
                    pos = it + 1;
                }
            }
        }
        if (std::distance(pos, end) != 0)
        {
            splits.emplace_back(pos, end);
        }
        return splits;
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD std::vector<std::basic_string<char_t>> split(const std::basic_string<char_t> &str1, const std::basic_string<char_t> &str2) noexcept
    {
        return split(str1.begin(), str1.end(), str2);
    }

    template <typename _Elem = char>
    void keep(std::basic_string<_Elem> &str, const std::basic_string<_Elem> &safe) noexcept
    {
        bool ok;
        for (auto it = str.begin(); it != str.end(); ++it)
        {
            ok = false;
            for (auto it2 = safe.begin(); it2 != safe.end(); ++it2)
            {
                if (*it == *it2)
                {
                    ok = true;
                    break;
                }
            }
            if (!ok)
            {
                *it = ' ';
            }
        }
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD auto ocurrences(typename std::basic_string<char_t>::const_iterator begin, typename std::basic_string<char_t>::const_iterator end,
                                       const char_t &character) noexcept
    {
        size_t value = 0;
        for (auto it = begin; it != end; ++it)
        {
            if (*it == character)
            {
                value += 1;
            }
        }
        return value;
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD auto ocurrences(const std::basic_string<char_t> &str, const char_t &character) noexcept
    {
        return ocurrences(str.begin(), str.end(), character);
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD constexpr bool match_begin(typename std::basic_string<char_t>::const_iterator begin, typename std::basic_string<char_t>::const_iterator end, const std::basic_string<char_t> &str) noexcept
    {
        if (std::distance(begin, end) < str.size())
        {
            return false;
        }
        bool found = true;
        for (auto it1 = begin, it2 = str.begin(); it2 != str.end(); ++it1, ++it2) // it1 != begin + str.size() && 
        {
            if(*it1 != *it2)
            {
                found = false;
                break;
            }
        }
        return found;
    }

    template <typename char_t = char>
    _GLIBCXX_NODISCARD constexpr bool match_begin(const std::basic_string<char_t> &str1, const std::basic_string<char_t> &str2) noexcept
    {
        return match_begin(str1.begin(), str2.end(), str2);
    }


} // namespace end
