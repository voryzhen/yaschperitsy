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
                                       _renderer)
                    ->run_game();
            }
        }

        ~App() { cleanup(); }

        App(const App&) = delete;
        App& operator=(const App&) = delete;

    private:
        bool init_sdl();
        void cleanup();

        SDL_Renderer* _renderer{nullptr};
        SDL_Window* _window{nullptr};

        static constexpr int SCREEN_WIDTH{1280};
        static constexpr int SCREEN_HEIGHT{720};
        static constexpr std::string_view title = "Ящперицы";
};
