#pragma once
#include <iostream>
#include <functional>

#include "console.h"
#include "log.h"

namespace saheki::dialogs
{
    template <typename char_type = char>
    _GLIBCXX_NODISCARD bool qyestion_confirm(std::string question, bool default_option = true) noexcept
    {
        std::basic_string<char_type> valid_yes[5] = {"y", "Y", "yes", "YES", "Yes"};
        std::basic_string<char_type> valid_no[5] = {"n", "N", "no", "NO", "No"};

        std::basic_string<char_type> answer;

        while (true)
        {
            if (default_option)
            {
                log::console_(":: ", question, " [Y/n]: ");
            }
            else
            {
                log::console_(":: ", question, " [y/N]: ");
            }

            answer = console::input<char_type>();

            if (answer == "")
            {
                return default_option;
            }
            for (auto it = 0; it != 5; ++it)
            {
                if (answer == valid_yes[it])
                {
                    return true;
                }
            }
            for (auto it = 0; it != 5; ++it)
            {
                if (answer == valid_yes[it])
                {
                    return false;
                }
            }
            log::console("Sorry, try again.");
        }
    }

    template <typename char_type = char>
    _GLIBCXX_NODISCARD constexpr std::basic_string<char_type> question(const std::basic_string<char_type> &demand,
                                                                       const std::function<bool(std::basic_string<char_type>)> &fn) noexcept
    {
        std::basic_string<char_type> answer;
        log::console_(":: ", demand, " ");
        while (true)
        {
            answer = console::input_line<char_type>();
            if (fn(answer))
            {
                return answer;
            }
        }
    }

} // namespace end