#pragma once

#include "core/App.h"
#include "core/Layer.h"
#include "core/events/Event.h"
#include <memory>

namespace yaschperitsy::game
{

class ExampleLayer : public core::Layer
{
    public:
        ExampleLayer() : core::Layer("Example") {}

        void on_update()
        {
            core::logging::Logger::get_logger()->info(
                "Example Layer Updated");
        }

        void on_event(const core::events::EventSPtr& event)
        {
            core::logging::Logger::get_logger()->info(
                event->as_string());
        }
};

class NewGame : public core::App
{
    public:
        NewGame()
        {
            int g = 1;
            push_layer(std::make_shared<ExampleLayer>());
        }

        NewGame(bool old) : App(old) {}

        ~NewGame() {}
};

}; // namespace yaschperitsy::game
