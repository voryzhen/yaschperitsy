#include "boost/test/unit_test.hpp"

#include "app/events/KeyEvent.h"
#include <string>

BOOST_AUTO_TEST_SUITE(events_system_keyboard_events_unit_tests_suite)

BOOST_AUTO_TEST_CASE(keyboard_pressed_event_test)
{
    using namespace yaschperitsy::core::events;

    KeyPressedEvent e(50, true);

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryKeyboard));
    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryInput));
    BOOST_CHECK(
        e.category_flags() ==
        (static_cast<int>(EventCategory::EventCategoryKeyboard) |
         static_cast<int>(EventCategory::EventCategoryInput)));

    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryApp));

    BOOST_CHECK(e.name() == std::string{"KeyPressed"});
    BOOST_CHECK(e.as_string() == "KeyPressedEvent: 50 (repeated true)");
    BOOST_CHECK(e.static_type() == EventType::KeyPressed);

    BOOST_CHECK(e.key_code() == 50);
    BOOST_CHECK(e.repeated() == true);
}

BOOST_AUTO_TEST_CASE(keyboard_released_event_test)
{
    using namespace yaschperitsy::core::events;

    KeyReleasedEvent e(50);

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryKeyboard));
    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryInput));
    BOOST_CHECK(
        e.category_flags() ==
        (static_cast<int>(EventCategory::EventCategoryKeyboard) |
         static_cast<int>(EventCategory::EventCategoryInput)));

    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryApp));

    BOOST_CHECK(e.name() == std::string{"KeyReleased"});
    BOOST_CHECK(e.as_string() == "KeyReleasedEvent: 50");
    BOOST_CHECK(e.static_type() == EventType::KeyReleased);

    BOOST_CHECK(e.key_code() == 50);
}

BOOST_AUTO_TEST_SUITE_END()
