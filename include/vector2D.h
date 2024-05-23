#pragma once

class Vector2D
{
    public:
        Vector2D() = default;

        Vector2D(float x, float y) : _x(x), _y(y) {}

        Vector2D& operator+=(const Vector2D& vec);
        Vector2D& operator-=(const Vector2D& vec);
        Vector2D& operator*=(const Vector2D& vec);
        Vector2D& operator/=(const Vector2D& vec);

        Vector2D operator+(const Vector2D& vec) const;
        Vector2D operator-(const Vector2D& vec) const;
        Vector2D operator*(const Vector2D& vec) const;
        Vector2D operator/(const Vector2D& vec) const;

    private:
        float _x{.0f};
        float _y{.0f};
};
