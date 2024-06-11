#pragma once

#include "SDL_events.h"
#include "SDL_video.h"
#include <array>
#include <memory>
#include <resource_manager.h>
#include <string_view>

#include <game.h>

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
        App& operator=(const App&) = delete;

    private:
        static bool init_sdl();
        static void cleanup();

        static SDL_WindowPtr _window;
        static SDL_RendererPtr _renderer;

        static ResourceManagerPtr _rm;

        static constexpr int SCREEN_WIDTH{1280};
        static constexpr int SCREEN_HEIGHT{720};
        static constexpr std::string_view title = "Ящперицы";

        static constexpr int _renderer_flags{SDL_RENDERER_ACCELERATED};
        static constexpr int _window_flags{0};
};
