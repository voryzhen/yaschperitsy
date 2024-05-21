#pragma once

#include <memory>
#include <string_view>

#include <game.h>

class App
{
    public:
        App()
        {
            if (init_sdl())
            {
                std::make_unique<Game>(SCREEN_WIDTH, SCREEN_HEIGHT,
                                       _renderer.get())
                    ->run_game();
            }
        }

        ~App() { cleanup(); }

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
};
