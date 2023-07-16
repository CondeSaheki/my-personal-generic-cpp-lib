#include <iostream>
#include <cmath>

namespace gamer
{

    // coordinates

    template <typename type = int8_t>
    class coordinates
    {
    public: // type
        using _type = type;

    public: // data
        type X;
        type Y;

    public: // constructors
        template <typename a>
        coordinates(type &&x, type &&y) : X(static_cast<type>(x)), Y(static_cast<type>(y)) {}
        coordinates(const type &x, const type &y) : X(static_cast<type>(x)), Y(static_cast<type>(y)) {}
        coordinates() : X(0), Y(0) {}

    public:
        double Distance(const coordinates<type> &b)
        {
            return std::sqrt((X - b.X) * (X - b.X) + (Y - b.Y) * (Y - b.Y));
        }
    };

    template <typename _CharT, typename type>
    std::basic_ostream<_CharT> &operator<<(std::basic_ostream<_CharT> &_Os, const coordinates<type> &cord)
    {
        return _Os << '<' << cord.X << ',' << cord.Y << '>';
    }

    template <typename type>
    bool operator==(const coordinates<type> &a, const coordinates<type> &b)
    {
        if (a.X == b.X && a.Y == b.Y)
            return true;
        return false;
    }

    // line things

    template <typename type = int8_t>
    class line
    {
    public: // data
        coordinates<type> a;
        coordinates<type> b;
        double AlgularCoeficient;

    public: // constructors
        line(coordinates<type> &&_a, coordinates<type> &&_b) : a(_a), b(_b), AlgularCoeficient(0) {}
        line(const coordinates<type> &_a, const coordinates<type> &_b) : a(_a), b(_b), AlgularCoeficient(0) {}

    public: // metods
        double CalculateAlgularCoeficient()
        {
            AlgularCoeficient = (a.Y - b.Y) / (a.X - b.X);
            return AlgularCoeficient;
        }
        double Distance(const coordinates<type> &c)
        {
            return ((b.X - a.X) * (a.Y - c.Y) - (a.X - c.X) * (b.Y - a.Y)) / b.Distance(a);
        }
    };

    template <typename type>
    double Angle(const coordinates<type> &a, const coordinates<type> &b, const coordinates<type> &c)
    {
        auto result = std::atan2(c.Y - b.Y, c.X - b.X) - std::atan2(a.Y - b.Y, a.X - b.X);
        if (result < 0)
            return result + std::numbers::pi * 2;
        return result;
    }

} // namespace end
