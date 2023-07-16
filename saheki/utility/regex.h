#pragma once
#include <string>
#include <regex>
#include <vector>
#include <functional>

namespace saheki::regex
{
    template <typename _Elem = char>
    void foreach (std::basic_string<_Elem> &str, const std::basic_regex<_Elem> &rgx,
                  const std::function<void(std::match_results<typename std::basic_string<_Elem>::iterator> &)> &lambda) noexcept
    {
        if (!str.empty()) // && !rgx._Empty()
        {
            typename std::basic_string<_Elem>::iterator match_it = str.begin();
            std::match_results<typename std::basic_string<_Elem>::iterator> rgx_matchs;
            auto state = std::regex_search(str.begin(), str.end(), rgx_matchs, rgx);
            while (std::regex_search(match_it, str.end(), rgx_matchs, rgx))
            {
                lambda(rgx_matchs);
                match_it = get<0>(rgx_matchs.suffix());
            }
        }
    }

    template <typename _Elem = char>
    void foreach (std::basic_string<_Elem> &str, const std::basic_string<_Elem> &rgx_str,
                  const std::function<void(std::match_results<typename std::basic_string<_Elem>::iterator> &)> &lambda) noexcept
    {
        foreach (str, std::basic_regex<_Elem>(rgx_str), lambda);
    }

    template <typename _Elem = char>
    constexpr void replace(std::basic_string<_Elem> &str, const std::basic_regex<_Elem> &rgx,
                        const std::function<void(std::basic_string<_Elem> &)> &edit_lambda) noexcept // void (*edit_lambda)(std::basic_string<_Elem> &str)
    {
        if (!str.empty()) // && !rgx._Empty()
        {
            typename std::basic_string<_Elem>::iterator match_it = str.begin();
            std::match_results<typename std::basic_string<_Elem>::iterator> rgx_matchs;
            std::basic_string<_Elem> sub_str;
            while (std::regex_search(match_it, str.end(), rgx_matchs, rgx))
            {
                sub_str = rgx_matchs.str();
                edit_lambda(sub_str);
                match_it = get<1>((rgx_matchs.prefix())) + sub_str.size();
                str.replace(get<1>((rgx_matchs.prefix())), get<0>((rgx_matchs.suffix())), sub_str.begin(), sub_str.end());
                sub_str.clear();
            }
        }
    }

    template <typename _Elem = char>
    void replace(std::basic_string<_Elem> &str, const std::basic_string<_Elem> &rgx_str,
              const std::function<void(std::basic_string<_Elem> &)> &edit_lambda) noexcept
    {
        replace(str, std::basic_regex<_Elem>(rgx_str), edit_lambda);
    }

} // namespace end