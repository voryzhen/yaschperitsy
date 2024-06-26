#pragma once

#include <app/ResourceManager.h>
#include <app/Window.h>
#include <iostream>
#include <ui/ScreenManager.h>

#include "SDL_events.h"
#include "app/Logger.h"
#include "app/events/Event.h"

namespace yaschperitsy::app
{

class App
{
    public:
        App();

        void on_event(const events::EventSPtr& event)
        {
            logging::Logger::get_logger()->info(event->as_string());
            if (event->event_type() == events::EventType::WindowClose)
            {
                _running = false;
            }
        }

    private:
        void run_app();

        void handle_events();
        void update();
        void render();

        SDL_Event _event{};
        bool _running = true;

        WindowUPtr _window;
        resource::ResourceManagerUPtr _resource_manager;
        ui::ScreenManagerUPtr _screen_manager;
};

} // namespace yaschperitsy::app
