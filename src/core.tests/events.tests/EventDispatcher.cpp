#include "boost/test/unit_test.hpp"

#include <core/events/AppEvent.hpp>
#include <core/events/Event.hpp>

BOOST_AUTO_TEST_SUITE(event_dispatcher_unit_tests_suite)

bool event_function_true(
    yaschperitsy::core::events::AppRenderEventSPtr e)
{
    return (e->as_string() == std::string{"AppRender"});
};

bool event_function_false(
    std::shared_ptr<yaschperitsy::core::events::AppRenderEvent> e)
{
    return !event_function_true(e);
};

BOOST_AUTO_TEST_CASE(event_dispatcher_test)
{

    using namespace yaschperitsy::core::events;

    EventSPtr e = std::make_shared<AppRenderEvent>();
    EventDispatcher ed(e);

    auto is_dispatched = ed.dispatch(
        std::function<bool(AppRenderEventSPtr)>(event_function_true));

    BOOST_CHECK(is_dispatched);
    BOOST_CHECK(e->is_handled());

    is_dispatched = ed.dispatch(
        std::function<bool(AppRenderEventSPtr)>(event_function_false));
    BOOST_CHECK(is_dispatched);
    BOOST_CHECK(!e->is_handled());
}

BOOST_AUTO_TEST_SUITE_END()
