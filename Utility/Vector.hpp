#pragma once

#include <cmath>
#include <numbers>

constexpr float rad = 180.0f / std::numbers::pi_v<float>;

template <typename T>
struct Vector2D
{
    public:
        Vector2D operator+(const Vector2D& vec) const
        {
            return { x + vec.x, y + vec.y };
        }

        Vector2D operator-(const Vector2D& vec) const
        {
            return { x - vec.x, y - vec.y };
        }

        Vector2D& operator+=(const Vector2D& vec)
        {
            x += vec.x;
            y += vec.y;
            return *this;
        }

        Vector2D& operator-=(const Vector2D& vec)
        {
            x -= vec.x;
            y -= vec.y;
            return *this;
        }

        Vector2D& operator*=(int factor)
        {
            auto float_factor = static_cast<T>(factor);
            x *= float_factor;
            y *= float_factor;
            return *this;
        }

        Vector2D operator*(int factor) const
        {
            auto float_factor = static_cast<T>(factor);
            return { x * float_factor, y * float_factor };
        }

        Vector2D& operator/=(int factor)
        {
            auto float_factor = static_cast<T>(factor);
            x /= float_factor;
            y /= float_factor;
            return *this;
        }

        Vector2D operator/(int factor) const
        {
            auto float_factor = static_cast<T>(factor);
            return { x / float_factor, y / float_factor };
        }

        void normalize()
        {
            auto length = sqrt(x * x + y * y);
            x = x / length;
            y = y / length;
        }

        float length() { return sqrt(x * x + y * y); }

        float angle() { return std::atan2(y, x) * rad; }

        T x {};
        T y {};
};

// TODO:

//======

/*

#pragma once

#include <cstdlib>

constexpr float eps = 1e-6;

template <typename T> class Vector2D
{

        Vector2D& operator*=(const Vector2D& vec)
        {
            _x *= vec._x;
            _y *= vec._y;
            return *this;
        }

        Vector2D& operator/=(const Vector2D& vec)
        {
            _x /= vec._x;
            _y /= vec._y;
            return *this;
        }



        bool operator==(const Vector2D& vec) const
        {
            return std::abs(_x - vec._x) < eps &&
                   std::abs(_y - vec._y) < eps;
        }

        bool operator!=(const Vector2D& vec) const
        {
            return !(*this == vec);
        }

    private:
        T _x{};
        T _y{};
};

*/