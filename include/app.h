#pragma once

#include <memory>
#include <string_view>

#include <game.h>

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

        static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>
            _window;
        static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>
            _renderer;

        static constexpr int SCREEN_WIDTH{1280};
        static constexpr int SCREEN_HEIGHT{720};
        static constexpr std::string_view title = "Ящперицы";

        static constexpr int _renderer_flags{SDL_RENDERER_ACCELERATED};
        static constexpr int _window_flags{0};
};
