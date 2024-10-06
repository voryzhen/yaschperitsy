#pragma once

#include <functional>
#include <ostream>
#include <string>
#include <utility>

enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
    External,
    Game
};

enum class EventCategory
{
    None = 0,
    // clang-format off
    EventCategoryApp         = 1u << 0u,
    EventCategoryInput       = 1u << 1u,
    EventCategoryKeyboard    = 1u << 2u,
    EventCategoryMouse       = 1u << 3u,
    EventCategoryMouseButton = 1u << 4u,
    EventCategoryExternal    = 1u << 5u,
    EventCategoryGame        = 1u << 6u
    // clang-format on
};

class Event
{
        friend class EventDispatcher;

    public:
        virtual EventType event_type() const = 0;
        virtual const char* name() const = 0;
        virtual unsigned int category_flags() const = 0;

        virtual std::string as_string() const { return name(); }

        inline bool is_in_category(EventCategory event_category) const
        {
            return (category_flags() &
                    static_cast<unsigned int>(event_category)) != 0;
        }

        virtual ~Event() = default;

        virtual bool is_handled() const { return _handled; }

    protected:
        bool _handled = false;
};

using EventSPtr = std::shared_ptr<Event>;

class EventDispatcher
{
    private:
        template <typename T>
        using EventFunction = std::function<bool(std::shared_ptr<T>)>;

    public:
        EventDispatcher(EventSPtr event) : _event(std::move(event)) {}

        template <typename T>
        bool dispatch(EventFunction<T> function)
        {
            if (_event->event_type() == T::static_type())
            {
                _event->_handled = function(static_pointer_cast<T>(_event));
                return true;
            }
            return false;
        }

    private:
        EventSPtr _event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& event)
{
    return os << event.as_string();
}
