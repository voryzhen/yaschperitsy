#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE vector_unit_tests
#define BOOST_TEST_DYN_LINK

#include "boost/test/unit_test.hpp"
#include "vector2D.h"

BOOST_AUTO_TEST_SUITE(vector_unit_tests_suite)

// NOLINTBEGIN(cppcoreguidelines-avoid-do-while)

BOOST_AUTO_TEST_CASE(vector_ctor)
{
    Vector2D a;
    Vector2D b(.5f, 999.444f);

    BOOST_CHECK(std::abs(a.x()) < eps && std::abs(a.y()) < eps);
    BOOST_CHECK(std::abs(b.x() - 0.5f) < eps &&
                std::abs(b.y() - 999.444f) < eps);
}

BOOST_AUTO_TEST_CASE(vector_equals_operators)
{
    Vector2D a(.4f, .5f);
    Vector2D b(.4f, .5f);
    Vector2D c(.5f, .4f);
    BOOST_CHECK(a == b);
    BOOST_CHECK(a != c);
}

BOOST_AUTO_TEST_CASE(vector_math_operators_plus)
{
    // a + b

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

BOOST_AUTO_TEST_CASE(vector_math_operators_minus)
{
    // a - b

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

BOOST_AUTO_TEST_CASE(vector_math_operators_plus_eq)
{
    // a += b

    Vector2D a(.5f, .6f);
    Vector2D b(.4f, .5f);

    a += b;

    Vector2D a1(.9f, 1.1f);
    Vector2D b1(.4f, .5f);

    BOOST_CHECK(a == a1);
    BOOST_CHECK(b == b1);
}

BOOST_AUTO_TEST_CASE(vector_math_operators_minus_eq)
{
    // a -= b

    Vector2D a(.5f, .6f);
    Vector2D b(.4f, .5f);

    a -= b;

    Vector2D a1(.1f, .1f);
    Vector2D b1(.4f, .5f);

    BOOST_CHECK(a == a1);
    BOOST_CHECK(b == b1);
}

BOOST_AUTO_TEST_CASE(vector_math_operators_mult_const)
{
    // a = b * const

    Vector2D a(.102f, .648f);
    Vector2D b(.51f, 3.24f);
    const int speed = 5;

    Vector2D c = a * speed;

    Vector2D a1(.102f, .648f);

    BOOST_CHECK(c == b);
    BOOST_CHECK(a == a1);
}

BOOST_AUTO_TEST_SUITE_END()

// NOLINTEND(cppcoreguidelines-avoid-do-while)
