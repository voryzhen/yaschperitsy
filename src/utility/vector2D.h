#pragma once

#include <cstdlib>

constexpr float eps = 1e-6;

template <typename T> class Vector2D
{
    public:
        Vector2D() = default;

        Vector2D(T x, T y) : _x(x), _y(y) {}

        T x() const { return _x; }

        T y() const { return _y; }

        void set_x(T x) { _x = x; }

        void set_y(T y) { _y = y; }

        Vector2D& operator+=(const Vector2D& vec)
        {
            _x += vec._x;
            _y += vec._y;
            return *this;
        }

        Vector2D& operator-=(const Vector2D& vec)
        {
            _x -= vec._x;
            _y -= vec._y;
            return *this;
        }

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

        Vector2D& operator*=(int factor)
        {
            auto float_factor = static_cast<T>(factor);
            _x *= float_factor;
            _y *= float_factor;
            return *this;
        }

        Vector2D operator+(const Vector2D& vec) const
        {
            return {_x + vec._x, _y + vec._y};
        }

        Vector2D operator-(const Vector2D& vec) const
        {
            return {_x - vec._x, _y - vec._y};
        }

        Vector2D operator*(const Vector2D& vec) const
        {
            return {_x * vec._x, _y * vec._y};
        }

        Vector2D operator/(const Vector2D& vec) const
        {
            return {_x / vec._x, _y / vec._y};
        }

        Vector2D operator*(int factor) const
        {
            auto float_factor = static_cast<T>(factor);
            return {_x * float_factor, _y * float_factor};
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
