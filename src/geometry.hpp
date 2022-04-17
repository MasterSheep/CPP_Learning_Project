#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <math.h>
#include <numeric>
#include <utility>

template <size_t d, typename type> struct Point
{
    std::array<type, d> values;

    Point() = default;

    template <typename... Args>
    Point(type t, Args&&... args) : values { t, static_cast<type>(std::forward<Args>(args))... }
    {
        static_assert(sizeof...(args) + 1 == d);
    }

    Point(type x, type y) : values { x, y } { static_assert(d == 2, "check the dimension !!"); }
    Point(type x, type y, type z) : values { x, y, z } { static_assert(d == 3, "check the dimension !!"); }

    type& x() { return values[0]; }
    type x() const { return values[0]; }

    type& y()
    {
        static_assert(d > 1, "check the dimension !!");
        return values[1];
    }
    type y() const
    {
        static_assert(d > 1, "check the dimension !!");
        return values[1];
    }

    type& z()
    {
        static_assert(d > 2, "check the dimension !!");
        return values[2];
    }
    type z() const
    {
        // static_assert(d > 2, "check the dimension !!");
        return values[2];
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](type value1, type value2) { return value1 + value2; });
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](type value1, type value2) { return value1 - value2; });
        return *this;
    }

    Point& operator*=(const type scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](type value) { return value * scalar; });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const type scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point& operator*=(const Point& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point operator-() const { return Point { -x(), -y(), -z() }; }

    type length() const
    {

        return std::sqrt(std::accumulate(values.begin(), values.end(), 0.0,
                                         [](type v1, type v2) { return v1 + v2 * v2; }));
    }

    type distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const type target_len = 1.0f)
    {
        const type current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("can't normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const type max_len)
    {
        assert(max_len > 0);

        const type current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};

inline void test_generic_points()
{
    auto p1 = Point<2, float>(2.0f, 5.0f);
    auto p2 = Point<2, float>(2.0f, 15.0f);
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3;
    p3 -= p1;
    //
}

using Point2D = Point<2, float>;
using Point3D = Point<3, float>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
