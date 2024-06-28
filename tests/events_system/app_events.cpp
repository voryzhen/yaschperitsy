#include "app/events/Event.h"
#include "boost/test/unit_test.hpp"

#include "app/events/AppEvent.h"
#include <string>

BOOST_AUTO_TEST_SUITE(events_system_app_events_unit_tests_suite)

BOOST_AUTO_TEST_CASE(app_window_resize_event_test)
{
    using namespace yaschperitsy::core::events;

    WindowResizeEvent e(1200, 100);

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryApp));
    BOOST_CHECK(e.category_flags() ==
                static_cast<int>(EventCategory::EventCategoryApp));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryInput));

    BOOST_CHECK(e.name() == std::string{"WindowResize"});
    BOOST_CHECK(e.as_string() == "WindowResizeEvent: 1200, 100");
    BOOST_CHECK(e.static_type() == EventType::WindowResize);

    BOOST_CHECK(e.width() == 1200);
    BOOST_CHECK(e.height() == 100);
}

BOOST_AUTO_TEST_CASE(app_window_close_event_test)
{
    using namespace yaschperitsy::core::events;

    WindowCloseEvent e;

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryApp));
    BOOST_CHECK(e.category_flags() ==
                static_cast<int>(EventCategory::EventCategoryApp));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryInput));

    BOOST_CHECK(e.name() == std::string{"WindowClose"});
    BOOST_CHECK(e.as_string() == "WindowClose");
    BOOST_CHECK(e.static_type() == EventType::WindowClose);
}

BOOST_AUTO_TEST_CASE(app_window_tick_event_test)
{
    using namespace yaschperitsy::core::events;

    AppTickEvent e;

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryApp));
    BOOST_CHECK(e.category_flags() ==
                static_cast<int>(EventCategory::EventCategoryApp));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryInput));

    BOOST_CHECK(e.name() == std::string{"AppTick"});
    BOOST_CHECK(e.as_string() == "AppTick");
    BOOST_CHECK(e.static_type() == EventType::AppTick);
}

BOOST_AUTO_TEST_CASE(app_window_update_event_test)
{
    using namespace yaschperitsy::core::events;

    AppUpdateEvent e;

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryApp));
    BOOST_CHECK(e.category_flags() ==
                static_cast<int>(EventCategory::EventCategoryApp));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryInput));

    BOOST_CHECK(e.name() == std::string{"AppUpdate"});
    BOOST_CHECK(e.as_string() == "AppUpdate");
    BOOST_CHECK(e.static_type() == EventType::AppUpdate);
}

BOOST_AUTO_TEST_CASE(app_window_render_event_test)
{
    using namespace yaschperitsy::core::events;

    AppRenderEvent e;

    BOOST_CHECK(e.is_in_category(EventCategory::EventCategoryApp));
    BOOST_CHECK(e.category_flags() ==
                static_cast<int>(EventCategory::EventCategoryApp));
    BOOST_CHECK(!e.is_in_category(EventCategory::EventCategoryInput));

    BOOST_CHECK(e.name() == std::string{"AppRender"});
    BOOST_CHECK(e.as_string() == "AppRender");
    BOOST_CHECK(e.static_type() == EventType::AppRender);
}

BOOST_AUTO_TEST_SUITE_END()
