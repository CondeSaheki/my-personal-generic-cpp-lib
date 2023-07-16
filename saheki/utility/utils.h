#pragma once
#include <vector>
#include <functional>

#include "../log.h"

namespace saheki::utils
{
    template <typename type>
    _GLIBCXX_NODISCARD constexpr auto map(const std::vector<type> &vec, const std::function<void(const type &)> &fn) noexcept
    {
        std::vector<type> result;
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            result.emplace_back(fn(*it));
        }
        return result;
    }

    template <typename type>
    _GLIBCXX_NODISCARD constexpr auto filter(const std::vector<type> &vec, const std::function<bool(const type &)> &fn) noexcept
    {
        std::vector<type> result;
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            if (fn(*it))
            {
                result.emplace_back(*it);
            }
        }
        return result;
    }

    template <typename type, typename vec_type>
    _GLIBCXX_NODISCARD constexpr auto reduce(const std::vector<vec_type> &vec, const std::function<type(const vec_type &)> &fn) noexcept
    {
        type accumulator;
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            accumulator += fn(*it);
        }
        return accumulator;
    }

    template <typename type, typename vec_type>
    _GLIBCXX_NODISCARD constexpr auto reduce_right(const std::vector<vec_type> &vec, const std::function<type(const vec_type &)> &fn) noexcept
    {
        type accumulator;
        for (auto it = vec.end() - 1; it != vec.begin(); --it)
        {
            accumulator += fn(*it);
        }
        return accumulator;
    }

    template <typename Elem>
    _GLIBCXX_NODISCARD constexpr inline bool next_ok(typename Elem::const_iterator it, typename Elem::const_iterator end) noexcept
    {
        if (it != end && it + 1 != end)
        {
            return true;
        }
        return false;
    }

    template <typename Elem>
    _GLIBCXX_NODISCARD constexpr inline bool prev_ok(typename Elem::const_iterator it, typename Elem::const_iterator begin) noexcept
    {
        if (it != begin)
        {
            return true;
        }
        return false;
    }



} // namespace end
