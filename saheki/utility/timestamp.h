#pragma once
#include <sstream>
#include <string>
#include <chrono>

/* STATICS */

template <typename _Elem = char, typename final_dur, typename dur>
_GLIBCXX_NODISCARD static inline constexpr final_dur func(std::basic_stringstream<_Elem> &ss) noexcept
{
    auto num = dur().count();
    if (!((ss) >> num))
    {
        (ss).clear();
        return std::chrono::floor<final_dur>(dur());
    }
    (ss).clear();
    return std::chrono::floor<final_dur>(dur(num));
}

template <typename _Elem = char, typename final_dur, typename duration, typename duration2, typename... the_rest>
static inline constexpr final_dur func(std::basic_stringstream<_Elem> &ss) noexcept
{
    return func<_Elem, final_dur, duration>(ss) + func<_Elem, final_dur, duration2, the_rest...>(ss);
}

/* NAMESPACE */

namespace saheki::timestamp
{
    template <typename _Elem = char, typename final_dur, typename duration, typename... other_dur>
    _GLIBCXX_NODISCARD constexpr final_dur conversor(const std::basic_string<_Elem> &str) noexcept
    {
        std::basic_stringstream<_Elem> ss(str);
        // to do flip template parameters
        final_dur temp_duration(func<_Elem, final_dur, duration, other_dur...>(ss));
        ss.clear();
        return temp_duration;
    }

    template <typename _Elem = char, typename final_dur, typename duration, typename... other_dur>
    void conversor_string(std::basic_string<_Elem> &str) noexcept
    {
        std::basic_stringstream<_Elem> ss(str);
        // to do flip template parameters
        final_dur temp_duration(func<_Elem, final_dur, duration, other_dur...>(ss));
        ss.str(std::basic_string<_Elem>());
        ss.clear();
        ss << temp_duration.count();
        str.clear();
        ss >> str;
    }
} // namespace end
