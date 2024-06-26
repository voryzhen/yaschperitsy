#pragma once

#include <memory>
#include <sstream>

#include <app/events/Event.h>

namespace yaschperitsy::app::events
{

class MouseMovedEvent : public Event
{
    public:
        MouseMovedEvent(int x, int y) : _x_pos(x), _y_pos(y) {}

        inline int x_pos() const { return _x_pos; }

        inline int y_pos() const { return _y_pos; }

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << _x_pos << ", " << _y_pos;
            return ss.str();
        }

        static EventType static_type() { return EventType::MouseMoved; }

        virtual EventType event_type() const override
        {
            return static_type();
        }

        virtual const char* name() const override
        {
            return "MouseMoved";
        }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                       EventCategory::EventCategoryMouse) |
                   static_cast<unsigned int>(
                       EventCategory::EventCategoryInput);
        }

    private:
        int _x_pos = 0;
        int _y_pos = 0;
};

class MouseScrolledEvent : public Event
{
    public:
        MouseScrolledEvent(float x_offset, float y_offset)
            : _x_offset(x_offset), _y_offset(y_offset)
        {
        }

        inline float x_offset() const { return _x_offset; }

        inline float y_offset() const { return _y_offset; }

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << _x_offset << ", "
               << _y_offset;
            return ss.str();
        }

        static EventType static_type()
        {
            return EventType::MouseScrolled;
        }

        virtual EventType event_type() const override
        {
            return static_type();
        }

        virtual const char* name() const override
        {
            return "MouseScrolled";
        }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                       EventCategory::EventCategoryMouse) |
                   static_cast<unsigned int>(
                       EventCategory::EventCategoryInput);
        }

    private:
        float _x_offset = 0;
        float _y_offset = 0;
};

class MouseButtonEvent : public Event
{
    public:
        inline int mouse_button() const { return _button; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                       EventCategory::EventCategoryMouse) |
                   static_cast<unsigned int>(
                       EventCategory::EventCategoryInput);
        }

    protected:
        MouseButtonEvent(int button) : _button(button) {}

        int _button = 0;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button)
        {
        }

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << _button;
            return ss.str();
        }

        static EventType static_type()
        {
            return EventType::MouseButtonPressed;
        }

        virtual EventType event_type() const override
        {
            return static_type();
        }

        virtual const char* name() const override
        {
            return "MouseButtonPressed";
        }
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button)
        {
        }

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << _button;
            return ss.str();
        }

        static EventType static_type()
        {
            return EventType::MouseButtonReleased;
        }

        virtual EventType event_type() const override
        {
            return static_type();
        }

        virtual const char* name() const override
        {
            return "MouseButtonReleased";
        }
};

using MouseMovedEventSPtr = std::shared_ptr<MouseMovedEvent>;
using MouseScrolledEventSPtr = std::shared_ptr<MouseScrolledEvent>;
using MouseButtonPressedEventSPtr =
    std::shared_ptr<MouseButtonPressedEvent>;
using MouseButtonReleasedEventSPtr =
    std::shared_ptr<MouseButtonReleasedEvent>;

}; // namespace yaschperitsy::app::events
