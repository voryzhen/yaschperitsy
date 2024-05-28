#pragma once

constexpr float eps = 1e-6;

class Vector2D
{
    public:
        Vector2D() = default;

        Vector2D(float x, float y) : _x(x), _y(y) {}

        float x() const { return _x; }

        float y() const { return _y; }

        Vector2D& operator+=(const Vector2D& vec);
        Vector2D& operator-=(const Vector2D& vec);
        Vector2D& operator*=(const Vector2D& vec);
        Vector2D& operator/=(const Vector2D& vec);

        Vector2D& operator*=(int factor);

        Vector2D operator+(const Vector2D& vec) const;
        Vector2D operator-(const Vector2D& vec) const;
        Vector2D operator*(const Vector2D& vec) const;
        Vector2D operator/(const Vector2D& vec) const;

        Vector2D operator*(int factor) const;

        bool operator==(const Vector2D& vec) const;
        bool operator!=(const Vector2D& vec) const;

    private:
        float _x{.0f};
        float _y{.0f};
};
