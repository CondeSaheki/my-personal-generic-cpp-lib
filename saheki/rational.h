#pragma once
#include <iostream>

namespace saheki
{

    template <typename type = int >
    class rational // must be numeric
    {
    public:
        type numerator;
        type denominator;

    public:
        constexpr rational()
            : numerator(static_cast<type>(1)),
              denominator(static_cast<type>(1)) {}
        template <typename t1>
        constexpr rational(const t1 &first)
            : numerator(static_cast<type>(first)),
              denominator(static_cast<type>(1)) {}
        template <typename t1, typename t2>
        constexpr rational(const t1 &first, const t2 &second)
            : numerator(static_cast<type>(first)),
              denominator(static_cast<type>(second)) {}

    public:
        _GLIBCXX_NODISCARD constexpr inline bool is_valid() noexcept
        {
            if (denominator == static_cast<type>(0))
            {
                return false;
            }
            return true;
        }
        void simplify() noexcept
        {
            if (!is_valid())
            {
                return;
            }

            if (numerator == denominator)
            {
                numerator = 1;
                denominator = 1;
                return;
            }

            for (auto i = std::abs(numerator - denominator); i != 1; --i)
            {
                if (numerator % i == 0 && denominator % i == 0)
                {
                    numerator /= i;
                    denominator /= i;
                    break;
                }
            }
        }
    };
} //namespace end
