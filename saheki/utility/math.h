#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

namespace saheki::math
{
    template <typename t>
    _GLIBCXX_NODISCARD inline constexpr bool is_positive(const t &num) noexcept
    {
        if (num > 0)
        {
            return true;
        }
        return false;
    }

    template <typename t>
    _GLIBCXX_NODISCARD inline constexpr bool is_negative(const t &num) noexcept
    {
        if (num < 0)
        {
            return true;
        }
        return false;
    }

    template <typename t>
    _GLIBCXX_NODISCARD inline constexpr bool is_null(const t &num) noexcept
    {
        if (num == 0)
        {
            return true;
        }
        return false;
    }

    template <size_t num_decimals, typename from>
    _GLIBCXX_NODISCARD constexpr from round_near(const from &value) noexcept
    {
        auto copy = value * powl(10, num_decimals);
        auto casted = static_cast<size_t>(copy);
        from decimals(0);
        if (value >= 0)
        {
            decimals = copy - casted;
            if (decimals >= 0.5)
            {
                casted = casted + 1;
            }
        }
        else
        {
            decimals = casted - copy;
            if (decimals <= 0.5)
            {
                casted = casted + 1;
            }
        }
        return static_cast<from>(casted) / powl(10, num_decimals);
    }

    template <typename type1, typename type2>
    _GLIBCXX_NODISCARD constexpr type1 media(std::vector<type2> &vec) noexcept
    {
        if (vec.empty())
        {
            return type1(0);
        }
        type1 result(0);
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            result += *it;
        }
        result /= vec.size();
        return result;
    }

    template <typename type1, typename type2>
    _GLIBCXX_NODISCARD constexpr type1 mediana(std::vector<type2> &vec) noexcept
    {
        if (vec.empty())
        {
            return type1(0);
        }

        std::vector<type2 *> reference;
        reference.reserve(vec.size());
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            reference.emplace_back(&(*it));
        }

        std::sort(reference.begin(), reference.end(),
                  [](const type2 *i, type2 *j)
                  {
                      return (*i < *j);
                  });

        if ((reference.size() + 1) % 2 == 0)
        {
            return *reference[reference.size() / 2];
        }
        return type1(*reference[size_t(reference.size() / 2) - 1] + *reference[size_t(reference.size() / 2)]) / 2;
    }
    
} // namespace end