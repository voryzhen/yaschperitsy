#pragma once

#include "SDL_events.h"
#include "SDL_pixels.h"
#include <resource_manager.h>
#include <ui/screen_manager.h>
#include <window.h>

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
        SDL_Color default_renderer_color = {28, 28, 28, 255};

        WindowUPtr _window;
        ResourceManagerUPtr _rm;
        ScreenManagerUPtr _sm;
};
