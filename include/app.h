#pragma once

#include "SDL_pixels.h"
#include <resource_manager.h>
#include <ui/start_screen.h>
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

        bool is_running = true;
        SDL_Color default_renderer_color = {128, 128, 128, 255};

        WindowUPtr _window;
        SDL_RendererSPtr _renderer;
        ResourceManagerUPtr _rm;
        StartScreenUPtr _ss;
};
