#pragma once

#include <core/events/Event.hpp>
#include <memory>
#include <sstream>

namespace yaschperitsy::game::events
{

class UIEvent : public yaschperitsy::core::events::Event
{
    public:
        UIEvent() = default;

        UIEvent(int code) : _code(code) {}

        inline int code() const { return _code; }

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "UIEvent: code" << _code;
            return ss.str();
        }

        static yaschperitsy::core::events::EventType static_type()
        {
            return yaschperitsy::core::events::EventType::External;
        }

        virtual yaschperitsy::core::events::EventType
        event_type() const override
        {
            return static_type();
        }

        virtual const char* name() const override { return "UIEvent"; }

        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                yaschperitsy::core::events::EventCategory::
                    EventCategoryExternal);
        }

    private:
        int _code{0};
};

using UIEventSPtr = std::shared_ptr<UIEvent>;

}; // namespace yaschperitsy::game::events
