#pragma once

#include <format>
#include <memory>
#include <sstream>

#include "Event.hpp"

class KeyEvent : public Event
{
    public:
        virtual unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(
                       EventCategory::EventCategoryKeyboard) |
                   static_cast<unsigned int>(EventCategory::EventCategoryInput);
        }

        inline int key_code() const { return _key_code; }

        inline int key_sym() const { return _key_sym; }

    protected:
        KeyEvent(int key_code, int key_sym)
            : _key_code(key_code), _key_sym(key_sym)
        {
        }

        int _key_code = 0;
        int _key_sym = 0;
};

class KeyPressedEvent : public KeyEvent
{
    public:
        KeyPressedEvent(int key_code, int key_sym, bool repeated)
            : KeyEvent(key_code, key_sym), _repeated(repeated)
        {
        }

        inline bool repeated() const { return _repeated; }

        std::string as_string() const override
        {
            return std::format("KeyPressedEvent: {} (repeated {})", _key_code,
                               _repeated ? "true" : "false");
        }

        static EventType static_type() { return EventType::KeyPressed; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "KeyPressed"; }

    private:
        bool _repeated = false;
};

class KeyReleasedEvent : public KeyEvent
{
    public:
        KeyReleasedEvent(int key_code, int key_sym)
            : KeyEvent(key_code, key_sym)
        {
        }

        std::string as_string() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << _key_code;
            return ss.str();
        }

        static EventType static_type() { return EventType::KeyReleased; }

        virtual EventType event_type() const override { return static_type(); }

        virtual const char* name() const override { return "KeyReleased"; }
};

using KeyPressedEventSPtr = std::shared_ptr<KeyPressedEvent>;
using KeyReleasedEventSPtr = std::shared_ptr<KeyReleasedEvent>;
