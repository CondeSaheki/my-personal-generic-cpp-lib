#pragma once
#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>

namespace saheki
{
    template <typename _type = bool>
    class validable // must be default construtible and have assing operator removed due to gcc bug
    {
    public: // type
        using type = _type;

    private: // data
        bool _valid;
        type _data;

    public: // constructors
        constexpr validable() : _valid(false), _data(type()) {}
        template <typename t>
        constexpr validable(const t &val) : _valid(true), _data(static_cast<type>(val)) {}
        // template<> constexpr validable(const type& val) : _valid(true), _data(val) {} // gcc bug

    public: // functions
        _GLIBCXX_NODISCARD constexpr bool is_valid() noexcept
        {
            return _valid;
        }
        void invalidate() noexcept
        {
            _valid = false;
        }
        void validate() noexcept
        {
            _valid = true;
        }
        _GLIBCXX_NODISCARD constexpr const type &value() noexcept
        {
            return _data;
        }
        _GLIBCXX_NODISCARD constexpr type &reference() noexcept
        {
            return _data;
        }
        template <typename t>
        void set(const t &val) noexcept
        {
            _data = type(val);
            _valid = true;
        }
        // template<> void set(const type& val) noexcept { _data = val; _valid = true; }  // gcc bug
        void reset()
        {
            _data = type();
            _valid = false;
        }

    public: // conversion operator
        operator type()
        {
            return _data;
        }

        // public: // I and O operators
        //     template <typename _CharT, typename type>
        //     friend std::basic_ostream<_CharT> &operator<<(std::basic_ostream<_CharT> &_Os, const validable<type> &_Right) noexcept;
        //     template <typename _CharT, typename type>
        //     friend std::basic_istream<_CharT> &operator>>(std::basic_istream<_CharT> &_Is, const validable<type> &_Right);
    };

    // /* operators */
    // template <typename _CharT, typename type>
    // std::basic_ostream<_CharT> &
    // operator<<(std::basic_ostream<_CharT> &_Os, const validable<type> &_Right) noexcept
    // {
    //     return _Os << '<' << "valid: " << (_Right._valid ? "true" : "false") << " | data: " << _Right._data << '>';
    // }
    // template <typename _CharT, typename type>
    // std::basic_istream<_CharT> &
    // operator>>(std::basic_istream<_CharT> &_Is, const validable<type> &_Right)
    // {
    //     /* not yet implemented */
    //     // read obj from stream
    //     if (false /* no valid object of T found in stream */)
    //     {
    //         _Is.setstate(std::ios::failbit);
    //     }
    //     return _Is;
    // }

} // namespace end

/* no needed any basic operation is better done directly and <=> operator is the same, the validity check shoud be decided by the programer when to happen.

// basic operators
        nodiscard constexpr validable<type> operator+() const noexcept
        {
            return validable<type>(*this);
        }
        nodiscard constexpr validable<_type> operator-() const noexcept
        {
            return validable<type>(-_data);
        }
        constexpr validable<type>& operator++() noexcept
        {
            ++_data;
            return *this;
        }
        constexpr validable<type> operator++(int) noexcept
        {
            return validable<type>(_data++);
        }
        constexpr validable<type>& operator--() noexcept
        {
            --_data;
            return *this;
        }
        constexpr validable<type> operator--(int) noexcept
        {
            return validable<type>(_data--);
        }
        // aritimetic operators
        nodiscard constexpr validable<type> operator+(const type& _Right) const noexcept
        {
            return validable<type>(_data + _Right);
        }
        nodiscard constexpr validable<type> operator+(const validable<type>& _Right) const noexcept
        {
            return validable<type>(_data + _Right._data);
        }
        nodiscard constexpr validable<type> operator-(const type& _Right) const noexcept
        {
            return validable<type>(_data - _Right);
        }
        nodiscard constexpr validable<type> operator-(const validable<type>& _Right) const noexcept
        {
            return validable<type>(_data - _Right._data);
        }
        nodiscard constexpr validable<type> operator*(const type& _Right) const noexcept
        {
            return validable<type>(_data * _Right);
        }
        nodiscard constexpr validable<type> operator*(const validable<type>& _Right) const noexcept
        {
            return validable<type>(_data * _Right._data);
        }
        nodiscard constexpr validable<type> operator/(const type& _Right) const noexcept
        {
            return validable<type>(_data / _Right);
        }
        nodiscard constexpr validable<type> operator/(const validable<type>& _Right) const noexcept
        {
            return validable<type>(_data / _Right._data);
        }
        nodiscard constexpr validable<type> operator%(const type& _Right) const noexcept
        {
            return validable<type>(_data % _Right);
        }
        nodiscard constexpr validable<type> operator%(const validable<type>& _Right) const noexcept
        {
            return validable<type>(_data % _Right._data);
        }
        nodiscard constexpr validable<type>& operator+=(const type& _Right) noexcept
        {
            _data += _Right;
            return *this;
        }
        nodiscard constexpr validable<type>& operator+=(const validable<type>& _Right) noexcept
        {
            _data += _Right._data;
            return *this;
        }
        nodiscard constexpr validable<type>& operator-=(const type& _Right) noexcept
        {
            _data -= _Right;
            return *this;
        }
        nodiscard constexpr validable<type>& operator-=(const validable<type>& _Right) noexcept
        {
            _data -= _Right._data;
            return *this;
        }
        nodiscard constexpr validable<type>& operator*=(const type& _Right) noexcept
        {
            _data *= _Right;
            return *this;
        }
        nodiscard constexpr validable<type>& operator*=(const validable<type>& _Right) noexcept
        {
            _data *= _Right._data;
            return *this;
        }
        nodiscard constexpr validable<type>& operator/=(const type& _Right) noexcept
        {
            _data /= _Right;
            return *this;
        }
        nodiscard constexpr validable<type>& operator/=(const validable<type>& _Right) noexcept
        {
            _data /= _Right._data;
            return *this;
        }
        nodiscard constexpr validable<type>& operator%=(const type& _Right) noexcept
        {
            _data %= _Right;
            return *this;
        }
        nodiscard constexpr validable<type>& operator%=(const validable<type>& _Right) noexcept
        {
            _data %= _Right._data;
            return *this;
        }
         // comparison operator
        template<typename type>
            friend constexpr bool operator==(const validable<type>& _Left, const validable<type>& _Right) noexcept;
        template<typename type>
            friend constexpr std::strong_ordering operator<=>(const validable<type>& _Left, const validable<type>& _Right) noexcept;
            template<typename type> nodiscard constexpr std::strong_ordering
        operator<=>(const validable<type>& _Left, const validable<type>& _Right) noexcept
    {
        return _Left._data <=> _Right._data;
    }
    template<typename type> nodiscard constexpr bool
        operator==(const validable<type>& _Left, const validable<type>& _Right) noexcept
    {
        return _Left._data == _Right._data;
    }
*/