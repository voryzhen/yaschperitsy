#pragma once

#include <format>
#include <memory>
#include <sstream>

#include "Event.hpp"

class MouseMovedEvent : public Event
{
    public:
        MouseMovedEvent(int x, int y) : _x(x), _y(y) {}

        inline int x() const { return _x; }

        inline int y() const { return _y; }

        std::string as_string() const override
        {
            return std::format("MouseMovedEvent: {}, {}", _x, _y);
        }

        static EventType static_type() { return EventType::MouseMoved; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "MouseMoved"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                       EventCategory::EventCategoryMouse) |
                   static_cast<unsigned int>(EventCategory::EventCategoryInput);
        }

    private:
        int _x = 0;
        int _y = 0;
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
            return std::format("MouseScrolledEvent: {}, {}", _x_offset,
                               _y_offset);
        }

        static EventType static_type() { return EventType::MouseScrolled; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "MouseScrolled"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                       EventCategory::EventCategoryMouse) |
                   static_cast<unsigned int>(EventCategory::EventCategoryInput);
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
                   static_cast<unsigned int>(EventCategory::EventCategoryInput);
        }

        inline int x() const { return _x; }

        inline int y() const { return _y; }

    protected:
        MouseButtonEvent(int button, int x, int y)
            : _button(button), _x(x), _y(y)
        {
        }

        int _button = 0;
        int _x = 0;
        int _y = 0;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
    public:
        MouseButtonPressedEvent(int button, int x, int y)
            : MouseButtonEvent(button, x, y)
        {
        }

        std::string as_string() const override
        {
            return std::format("MouseButtonPressedEvent: {}", _button);
        }

        static EventType static_type() { return EventType::MouseButtonPressed; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override
        {
            return "MouseButtonPressed";
        }
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
    public:
        MouseButtonReleasedEvent(int button, int x, int y)
            : MouseButtonEvent(button, x, y)
        {
        }

        std::string as_string() const override
        {
            return std::format("MouseButtonReleasedEvent: {}", _button);
        }

        static EventType static_type()
        {
            return EventType::MouseButtonReleased;
        }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override
        {
            return "MouseButtonReleased";
        }
};

using MouseMovedEventSPtr = std::shared_ptr<MouseMovedEvent>;
using MouseScrolledEventSPtr = std::shared_ptr<MouseScrolledEvent>;
using MouseButtonPressedEventSPtr = std::shared_ptr<MouseButtonPressedEvent>;
using MouseButtonReleasedEventSPtr = std::shared_ptr<MouseButtonReleasedEvent>;
