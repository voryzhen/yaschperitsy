#pragma once

#include <app/Logger.h> // TODO: remove ?
#include <app/ResourceManager.h>
#include <app/Window.h>
#include <app/events/Event.h>
#include <ui/ScreenManager.h>

#include <SDL_events.h>

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
