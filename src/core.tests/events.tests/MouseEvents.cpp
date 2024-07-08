#include "boost/test/unit_test.hpp"

#include <core/events/MouseEvent.hpp>

BOOST_AUTO_TEST_SUITE(mouse_events_unit_tests_suite)

BOOST_AUTO_TEST_CASE(mouse_moved_event_test)
{
    using namespace yaschperitsy::core::events;

    MouseMovedEvent e(1200, 100);

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryMouse));
    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryInput));
    BOOST_CHECK(e.category_flags() ==
                (static_cast<int>(EventCategory::EventCategoryMouse) |
                 static_cast<int>(EventCategory::EventCategoryInput)));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryApp));

    BOOST_CHECK(e.name() == std::string{"MouseMoved"});
    BOOST_CHECK(e.as_string() == "MouseMovedEvent: 1200, 100");
    BOOST_CHECK(e.static_type() == EventType::MouseMoved);

    BOOST_CHECK(e.x_pos() == 1200);
    BOOST_CHECK(e.y_pos() == 100);
}

BOOST_AUTO_TEST_CASE(mouse_scrolled_event_test)
{
    using namespace yaschperitsy::core::events;

    MouseScrolledEvent e(1200, 100);

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryMouse));
    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryInput));
    BOOST_CHECK(e.category_flags() ==
                (static_cast<int>(EventCategory::EventCategoryMouse) |
                 static_cast<int>(EventCategory::EventCategoryInput)));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryApp));

    BOOST_CHECK(e.name() == std::string{"MouseScrolled"});
    BOOST_CHECK(e.as_string() == "MouseScrolledEvent: 1200, 100");
    BOOST_CHECK(e.static_type() == EventType::MouseScrolled);

    BOOST_CHECK(e.x_offset() == 1200);
    BOOST_CHECK(e.y_offset() == 100);
}

BOOST_AUTO_TEST_CASE(mouse_button_pressed_event_test)
{
    using namespace yaschperitsy::core::events;

    MouseButtonPressedEvent e(1, 15, 41);

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryMouse));
    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryInput));
    BOOST_CHECK(e.category_flags() ==
                (static_cast<int>(EventCategory::EventCategoryMouse) |
                 static_cast<int>(EventCategory::EventCategoryInput)));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryApp));

    BOOST_CHECK(e.name() == std::string{"MouseButtonPressed"});
    BOOST_CHECK(e.as_string() == "MouseButtonPressedEvent: 1");
    BOOST_CHECK(e.static_type() == EventType::MouseButtonPressed);

    BOOST_CHECK(e.mouse_button() == 1);
    BOOST_CHECK(e.x_pos() == 15);
    BOOST_CHECK(e.y_pos() == 41);
}

BOOST_AUTO_TEST_CASE(mouse_button_released_event_test)
{
    using namespace yaschperitsy::core::events;

    MouseButtonReleasedEvent e(2, 21, 81);

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryMouse));
    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryInput));
    BOOST_CHECK(e.category_flags() ==
                (static_cast<int>(EventCategory::EventCategoryMouse) |
                 static_cast<int>(EventCategory::EventCategoryInput)));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryApp));

    BOOST_CHECK(e.name() == std::string{"MouseButtonReleased"});
    BOOST_CHECK(e.as_string() == "MouseButtonReleasedEvent: 2");
    BOOST_CHECK(e.static_type() == EventType::MouseButtonReleased);

    BOOST_CHECK(e.mouse_button() == 2);
    BOOST_CHECK(e.x_pos() == 21);
    BOOST_CHECK(e.y_pos() == 81);
}

BOOST_AUTO_TEST_SUITE_END()
