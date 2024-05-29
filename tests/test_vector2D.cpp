#define BOOST_TEST_MAIN
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif

// NOLINTNEXTLINE(unused-includes)
#include "boost/test/unit_test.hpp"
#include "vector2D.h"

int add(int i, int j) { return i + j; }

// NOLINTBEGIN(cppcoreguidelines-avoid-do-while)

BOOST_AUTO_TEST_CASE(vector_ctor)
{
    Vector2D a;
    Vector2D b(.5f, 999.444f);

    BOOST_CHECK(std::abs(a.x()) < eps && std::abs(a.y()) < eps);
    BOOST_CHECK(std::abs(b.x() - 0.5f) < eps &&
                std::abs(b.y() - 999.444f) < eps);
}

BOOST_AUTO_TEST_CASE(test_eq)
{
    Vector2D a(.4f, .5f);
    Vector2D b(.4f, .5f);
    Vector2D c(.5f, .4f);
    BOOST_CHECK(a == b);
    BOOST_CHECK(a != c);
}

BOOST_AUTO_TEST_CASE(test_math)
{
    // a + b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.5f, .6f);
        Vector2D c(1.0f, 1.2f);

        Vector2D d = a + b;

        BOOST_CHECK(d == c);

        Vector2D a1(.5f, .6f);
        Vector2D b1(.5f, .6f);

        BOOST_CHECK(a == a1);
        BOOST_CHECK(b == b1);
    }
    // a - b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.4f, .5f);
        Vector2D c(.1f, .1f);

        Vector2D d = a - b;

        BOOST_CHECK(d == c);

        Vector2D a1(.5f, .6f);
        Vector2D b1(.4f, .5f);

        BOOST_CHECK(a == a1);
        BOOST_CHECK(b == b1);
    }
    // a += b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.4f, .5f);

        a += b;

        Vector2D a1(.9f, 1.1f);
        Vector2D b1(.4f, .5f);

        BOOST_CHECK(a == a1);
        BOOST_CHECK(b == b1);
    }
    // a -= b
    {
        Vector2D a(.5f, .6f);
        Vector2D b(.4f, .5f);

        a -= b;

        Vector2D a1(.1f, .1f);
        Vector2D b1(.4f, .5f);

        BOOST_CHECK(a == a1);
        BOOST_CHECK(b == b1);
    }
}

// NOLINTEND(cppcoreguidelines-avoid-do-while)
