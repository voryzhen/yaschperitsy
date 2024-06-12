#pragma once

#include "SDL_events.h"
#include "SDL_video.h"
#include "ui/start_screen.h"
#include <array>
#include <memory>
#include <resource_manager.h>
#include <string_view>

#include <game/game.h>

using SDL_WindowPtr =
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

using SDL_RendererPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class App
{
    public:
        App();
        ~App();

        App(const App&) = delete;
        App(const App&&) = delete;
        App& operator=(const App&) = delete;
        App& operator=(const App&&) = delete;

    private:
        static bool init_sdl();
        void cleanup();

        void run_app();
        void handle_events();
        void update();
        void render();

        static SDL_WindowPtr _window;
        static SDL_RendererPtr _renderer;

        static ResourceManagerPtr _rm;

        static bool is_running;

        static constexpr int SCREEN_WIDTH{1280};
        static constexpr int SCREEN_HEIGHT{720};
        static constexpr std::string_view title = "Ящперицы";

        static constexpr int _renderer_flags{SDL_RENDERER_ACCELERATED};
        static constexpr int _window_flags{0};

        std::unique_ptr<StartScreen> ss;
};
