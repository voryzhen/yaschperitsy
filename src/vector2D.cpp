#include "vector2D.h"

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
