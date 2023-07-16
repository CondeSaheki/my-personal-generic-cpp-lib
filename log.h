#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <mutex>

namespace sfs = std::filesystem;

namespace saheki
{
    class log
    {
    private: // types and configs
        // warnning changing this result in several string literals breaking
        using char_type = char;
        using string_type = std::basic_string<char_type>;
        static const inline sfs::path file_path = "app.log";
        static const inline char_type endline = char_type(10);
        std::basic_ostream<char_type> &out = std::cout;

    private: // data
        std::mutex lk;
        std::basic_ofstream<char_type> fs;

    public: // metods
        template <typename... args>
        static void console(const args &...Args) noexcept
        {
            Get().output(Args..., endline);
            Get().outputf(std::chrono::system_clock::now(), " [con] ", Args..., endline);
        }
        template <typename... args>
        static void console_(const args &...Args) noexcept
        {
            Get().output(Args...);
            Get().outputf(std::chrono::system_clock::now(), " [con] ", Args..., endline);
        }
        template <typename... args>
        static void debug(const args &...Args) noexcept
        {
            Get().outputf(std::chrono::system_clock::now(), " [deb] ", Args..., endline);
        }
        template <typename... args>
        static void info(const args &...Args) noexcept
        {
            Get().outputf(std::chrono::system_clock::now(), " [inf] ", Args..., endline);
        }
        template <typename... args>
        static void warnning(const args &...Args) noexcept
        {
            Get().outputf(std::chrono::system_clock::now(), " [war] ", Args..., endline);
        }
        template <typename... args>
        static void error(const args &...Args) noexcept
        {
            Get().outputf(std::chrono::system_clock::now(), " [err] ", Args..., endline);
        }
        template <typename... args>
        static void fatal(const args &...Args) noexcept
        {
            Get().outputf(std::chrono::system_clock::now(), " [fat] ", Args..., endline);
            exit(1);
        }

    private:
        template <typename... args>
        void output(const args &...Args)
        {
            std::lock_guard lock(lk);
            add(out, Args...);
        }
        template <typename... args>
        void outputf(const args &...Args) noexcept
        {
            std::lock_guard lock(lk);

            // this need to be improved

            std::basic_stringstream<char_type> ss;
            add(ss, Args...);
            auto str = ss.str();
            std::copy(str.begin(), str.end(), std::ostreambuf_iterator<char_type>(fs));
            if (fs.bad())
            {
                out << std::chrono::system_clock::now() << " [fat] stream is in bad state writing \"" << file_path << '\"' << endline;
                exit(1);
            }
        }
        template <typename stream, typename type>
        constexpr inline void add(stream &s, const type &val) noexcept
        {
            s << val;
        }
        template <typename stream, typename first, typename... args>
        constexpr inline void add(stream &s, const first &First, const args &...Args) noexcept
        {
            add(s, First);
            add(s, Args...);
        }

    private: // construction
        log()
        {
            fs.open(file_path, std::ios::out | std::ios::app);
            if (!fs.is_open())
            {
                out << std::chrono::system_clock::now() << " [fat] could not open \"" << file_path << '\"' << endline;
                exit(1);
            }
            fs.clear();
        }
        static log &Get()
        {
            static log instance;
            return instance;
        }
        ~log()
        {
            fs.close();
        }

    public: // operators
        log(const log &) = delete;
    };
} // namespace end
