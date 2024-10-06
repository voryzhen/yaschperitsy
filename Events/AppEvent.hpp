#pragma once

#include <format>
#include <memory>

#include "Event.hpp"

class WindowResizeEvent : public Event
{
    public:
        WindowResizeEvent(unsigned int width, unsigned int heigth)
            : _width(width), _heigth(heigth)
        {
        }

        inline unsigned int width() const { return _width; }

        inline unsigned int height() const { return _heigth; }

        std::string as_string() const override
        {
            return std::format("WindowResizeEvent: {}, {}", _width, _heigth);
        }

        static EventType static_type() { return EventType::WindowResize; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "WindowResize"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(EventCategory::EventCategoryApp);
        }

    private:
        unsigned int _width = 0;
        unsigned int _heigth = 0;
};

class WindowCloseEvent : public Event
{
    public:
        WindowCloseEvent() = default;

        static EventType static_type() { return EventType::WindowClose; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "WindowClose"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(EventCategory::EventCategoryApp);
        }
};

class AppTickEvent : public Event
{
    public:
        AppTickEvent() = default;

        static EventType static_type() { return EventType::AppTick; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "AppTick"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(EventCategory::EventCategoryApp);
        }
};

class AppUpdateEvent : public Event
{
    public:
        AppUpdateEvent() = default;

        static EventType static_type() { return EventType::AppUpdate; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "AppUpdate"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(EventCategory::EventCategoryApp);
        }
};

class AppRenderEvent : public Event
{
    public:
        AppRenderEvent() = default;

        static EventType static_type() { return EventType::AppRender; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "AppRender"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(EventCategory::EventCategoryApp);
        }
};

using WindowResizeEventSPtr = std::shared_ptr<WindowResizeEvent>;
using WindowCloseEventSPtr = std::shared_ptr<WindowCloseEvent>;
using AppTickEventSPtr = std::shared_ptr<AppTickEvent>;
using AppUpdateEventSPtr = std::shared_ptr<AppUpdateEvent>;
using AppRenderEventSPtr = std::shared_ptr<AppRenderEvent>;
