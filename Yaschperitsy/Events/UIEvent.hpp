#pragma once

#include <cstdint>
#include <format>
#include <memory>
#include <string_view>

#include "Events/Event.hpp"

enum class UIEventCode : uint8_t
{
    NewGame = 0,
    Settings,
    Exit,
    Pause,
    GameWin,
    GameOver
};

const auto get_code_name = [](UIEventCode code) -> std::string_view
{
    switch (code)
    {
        case UIEventCode::NewGame:
            return "NewGame";
        case UIEventCode::Settings:
            return "Settings";
        case UIEventCode::Exit:
            return "Exit";
        case UIEventCode::Pause:
            return "Pause";
        case UIEventCode::GameWin:
            return "Win";
        case UIEventCode::GameOver:
            return "Game Over";
        default:
            return "Error";
    };
};

class UIEvent : public Event
{
    public:
        explicit UIEvent(UIEventCode code) : code_(code) {}

        std::string as_string() const override
        {
            return std::format("UIEvent: {}", get_code_name(code_));
        }

        static EventType static_type() { return EventType::Game; }

        EventType event_type() const override { return static_type(); }

        const char* name() const override { return "UIEvent"; }

        unsigned int category_flags() const override
        {
            return static_cast<unsigned int>(EventCategory::EventCategoryGame);
        }

        inline UIEventCode code() const { return code_; }

    private:
        UIEventCode code_ { UIEventCode::Exit };
};

using UIEventSPtr = std::shared_ptr<UIEvent>;
