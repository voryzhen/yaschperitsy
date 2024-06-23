#pragma once

#include <app/ResourceManager.h>
#include <app/Window.h>
#include <ui/ScreenManager.h>

#include "SDL_events.h"

namespace yaschperitsy::app
{

class App
{
    public:
        App();

        ~App() {}

        App(const App&) = delete;
        App(const App&&) = delete;
        App& operator=(const App&) = delete;
        App& operator=(const App&&) = delete;

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
