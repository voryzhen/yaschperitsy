#pragma once

#include <memory>
#include <sstream>

#include <app/events/Event.h>

namespace yaschperitsy::core::events
{

class KeyEvent : public Event
{
    public:
        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                       EventCategory::EventCategoryKeyboard) |
                   static_cast<unsigned int>(
                       EventCategory::EventCategoryInput);
        }

        inline int key_code() const { return _key_code; }

    protected:
        KeyEvent(int key_code) : _key_code(key_code) {}

        int _key_code = 0;
};

class KeyPressedEvent : public KeyEvent
{
    public:
        KeyPressedEvent(int key_code, bool repeated)
            : KeyEvent(key_code), _repeated(repeated)
        {
        }

        inline bool repeated() const { return _repeated; }

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << _key_code << " (repeated "
               << (_repeated ? "true" : "false") << ")";
            return ss.str();
        }

        static EventType static_type() { return EventType::KeyPressed; }

        virtual EventType event_type() const override
        {
            return static_type();
        }

        virtual const char* name() const override
        {
            return "KeyPressed";
        }

    private:
        bool _repeated = false;
};

class KeyReleasedEvent : public KeyEvent
{
    public:
        KeyReleasedEvent(int key_code) : KeyEvent(key_code) {}

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << _key_code;
            return ss.str();
        }

        static EventType static_type()
        {
            return EventType::KeyReleased;
        }

        virtual EventType event_type() const override
        {
            return static_type();
        }

        virtual const char* name() const override
        {
            return "KeyReleased";
        }
};

using KeyPressedEventSPtr = std::shared_ptr<KeyPressedEvent>;
using KeyReleasedEventSPtr = std::shared_ptr<KeyReleasedEvent>;

}; // namespace yaschperitsy::core::events
