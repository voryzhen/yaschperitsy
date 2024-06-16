#include "boost/test/unit_test.hpp"

#include "ecs2/icomponent.h"

BOOST_AUTO_TEST_SUITE(ecs2_icomponent_unit_tests_suite)

BOOST_AUTO_TEST_CASE(get_component_type_id)
{
    BOOST_CHECK(yaschperitsy::ecs2::get_component_type_ID() == 0);
    BOOST_CHECK(yaschperitsy::ecs2::get_component_type_ID() == 1);
    BOOST_CHECK(yaschperitsy::ecs2::get_component_type_ID() == 2);
    BOOST_CHECK(yaschperitsy::ecs2::get_component_type_ID() == 3);
    BOOST_CHECK(yaschperitsy::ecs2::get_component_type_ID() == 4);
}

BOOST_AUTO_TEST_CASE(get_template_component_type_id)
{
    using namespace yaschperitsy::ecs2;

    // clang-format off

    class FirstComponent : public IComponent{};
    class SecondComponent : public IComponent{};
    class ThirdComponent : public IComponent{};
    class FourthComponent : public IComponent{};
    class FifthComponent : public IComponent{};

    // clang-format on

    // obtain and fix ID
    auto first_component_id = get_component_type_ID<FirstComponent>();
    auto second_component_id = get_component_type_ID<SecondComponent>();
    auto third_component_id = get_component_type_ID<ThirdComponent>();
    auto fourth_component_id = get_component_type_ID<FourthComponent>();
    auto fifth_component_id = get_component_type_ID<FifthComponent>();

    BOOST_CHECK(first_component_id == 5);
    BOOST_CHECK(second_component_id == 6);
    BOOST_CHECK(third_component_id == 7);
    BOOST_CHECK(fourth_component_id == 8);
    BOOST_CHECK(fifth_component_id == 9);

    // Check ID value
    BOOST_CHECK(get_component_type_ID<FifthComponent>() == 9);
    BOOST_CHECK(get_component_type_ID<ThirdComponent>() == 7);
    BOOST_CHECK(get_component_type_ID<FirstComponent>() == 5);
    BOOST_CHECK(get_component_type_ID<FourthComponent>() == 8);
    BOOST_CHECK(get_component_type_ID<SecondComponent>() == 6);
}

BOOST_AUTO_TEST_SUITE_END()
