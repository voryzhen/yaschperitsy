#include "game/vector2D.h"
#include <cstdlib>

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
    _x += vec._x;
    _y += vec._y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
    _x -= vec._x;
    _y -= vec._y;
    return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
    _x *= vec._x;
    _y *= vec._y;
    return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
    _x /= vec._x;
    _y /= vec._y;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec) const
{
    return {_x + vec._x, _y + vec._y};
}

Vector2D Vector2D::operator-(const Vector2D& vec) const
{
    return {_x - vec._x, _y - vec._y};
}

Vector2D Vector2D::operator*(const Vector2D& vec) const
{
    return {_x * vec._x, _y * vec._y};
}

Vector2D Vector2D::operator/(const Vector2D& vec) const
{
    return {_x / vec._x, _y / vec._y};
}

bool Vector2D::operator==(const Vector2D& vec) const
{
    return std::abs(_x - vec._x) < eps && std::abs(_y - vec._y) < eps;
}

bool Vector2D::operator!=(const Vector2D& vec) const
{
    return !(*this == vec);
}

Vector2D& Vector2D::operator*=(int factor)
{
    auto float_factor = static_cast<float>(factor);
    _x *= float_factor;
    _y *= float_factor;
    return *this;
}

Vector2D Vector2D::operator*(int factor) const
{
    auto float_factor = static_cast<float>(factor);
    return {_x * float_factor, _y * float_factor};
}
