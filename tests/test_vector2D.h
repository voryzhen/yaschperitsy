#pragma once

#include "vector2D.h"
#include <cassert>
#include <cstdlib>
#include <iostream>

// TODO: refactor this nightmare with BOOST ?
// Boost is very big, but we are training

namespace test
{

// NOLINTNEXTLINE(misc-definitions-in-headers)
void test_ctor()
{
    Vector2D a;
    Vector2D b(.5f, 999.444f);
    assert(std::abs(a.x()) < eps && std::abs(a.y()) < eps);
    assert(std::abs(b.x() - 0.5f) < eps &&
           std::abs(b.y() - 999.444f) < eps);
}

// NOLINTNEXTLINE(misc-definitions-in-headers)
void test_eq()
{
    Vector2D a(.4f, .5f);
    Vector2D b(.4f, .5f);
    Vector2D c(.5f, .4f);
    assert(a == b);
    assert(a != c);
}

// NOLINTNEXTLINE(misc-definitions-in-headers)
void test_math()
{
    // a + b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.5f, .6f);
        Vector2D c(1.0f, 1.2f);

        Vector2D d = a + b;

        assert(d == c);

        Vector2D a1(.5f, .6f);
        Vector2D b1(.5f, .6f);

        assert(a == a1);
        assert(b == b1);
    }
    // a - b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.4f, .5f);
        Vector2D c(.1f, .1f);

        Vector2D d = a - b;

        std::cout << d.x() << " " << d.y() << " " << c.x() << " "
                  << c.y() << std::endl;

        assert(d == c);

        Vector2D a1(.5f, .6f);
        Vector2D b1(.4f, .5f);

        assert(a == a1);
        assert(b == b1);
    }
    // a += b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.4f, .5f);

        a += b;

        Vector2D a1(.9f, 1.1f);
        Vector2D b1(.4f, .5f);

        assert(a == a1);
        assert(b == b1);
    }
    // a -= b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.4f, .5f);

        a -= b;

        Vector2D a1(.1f, .1f);
        Vector2D b1(.4f, .5f);

        assert(a == a1);
        assert(b == b1);
    }
}

// NOLINTNEXTLINE(misc-definitions-in-headers)
void test()
{
    test_ctor();
    test_eq();
    test_math();
}

} // namespace test