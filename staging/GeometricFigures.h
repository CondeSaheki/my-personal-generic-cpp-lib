#include <array>
#include <numbers>
#include "Coordinates.h"

namespace gamer
{

template <typename type = int8_t >
class circle
{
public: // data
    double radius;
    coordinates<type> position;

public: // constructors
    circle() : radius(), position() {}
    circle(const double &_radius, const coordinates<type> &_position) : radius(_radius), position(_position) {}

public: // metods
    bool CheckColision(const coordinates<type> &point)
    {
        if (position.Distance(point) <= radius)
            return true;
        return false;
    }
};

template <uintmax_t sides = 4, typename type = int8_t >
class polygon
{
public: // asserts
    static_assert(sides >= 3, "<ERROR: invalid polygon, polygon must have more than 2 sides>");
public: // data
    std::array<coordinates<type>, sides> points;
public: // constructors
    polygon() : points() {}
    polygon(const std::array<coordinates<type>, sides> &_points) : points(_points) 
    {
        if (VerifyDuplicates() == true) std::cout << "<ERROR: invalid polygon, duplicated cordinates>" << std::endl;
        if (VerifyConcavo() == true) std::cout << "<ERROR: invalid polygon, concavo>" << std::endl;
    }
    polygon(std::array<coordinates<type>, sides> &&_points) : points(_points)
    {
        if (VerifyDuplicates() == true) std::cout << "<ERROR: invalid polygon, duplicated cordinates>" << std::endl;
        if (VerifyConcavo() == true) std::cout << "<ERROR: invalid polygon, concavo>" << std::endl;
    }
public: // metods
    bool CheckColision(const coordinates<type> &point)
    {
        for(auto it = points.begin(); it != points.end() - 1; ++it)
        {            
            if(-DistanceSpecial((*it), *std::next(it), point) < 0 ) return false;
        }
        if(-DistanceSpecial(*(points.end() - 1), *points.begin(), point) < 0 ) return false;
        return true;
    }
private:
    constexpr bool VerifyConcavo() noexcept
    {
        if constexpr (sides == 3) return false;
        for(auto it = points.begin(); it != points.end() - 2; ++it)
        {   
            if(Angle(*std::next(it, 2), *std::next(it), *it) >= std::numbers::pi ) return true;
        }
        if(Angle(*std::next(points.begin()), *points.begin(), *std::prev(points.end())) >= std::numbers::pi ) return true;
        if(Angle(*points.begin(), *std::prev(points.end()), *std::prev(points.end(), 2)) >= std::numbers::pi ) return true;
        return false;
    }
    constexpr bool VerifyDuplicates() noexcept
    {
        for(auto it = points.begin(); it != points.end(); ++it)
        {
            for(auto it2 = it + 1; it2 != points.end(); ++it2)
            {
                if(*it == *it2) return true;
            }
        }
        return false;
    }
    double DistanceSpecial(const coordinates<type>& a,const coordinates<type>& b,const coordinates<type>& c)
    {
        return (b.X - a.X)*(a.Y - c.Y) - (a.X - c.X)*(b.Y - a.Y);
    }
};
} // namespace end