#pragma once

#include <resource_manager.h>
#include <ui/screen_manager.h>
#include <window.h>

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

        SDL_Event event{};
        bool is_running = true;

        WindowUPtr _window;
        resource::ResourceManagerUPtr _rm;
        ScreenManagerUPtr _sm;
};

} // namespace yaschperitsy::app
