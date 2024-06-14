#pragma once

#include <memory>
#include <string_view>

#include <SDL_render.h>

using SDL_WindowUPtr =
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using SDL_RendererSPtr = std::shared_ptr<SDL_Renderer>;

class Window
{
    public:
        Window();
        ~Window();

        Window(const Window&) = delete;
        Window(const Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(const Window&&) = delete;

        SDL_RendererSPtr get_renderer() { return _renderer; }

        bool is_initialized() const { return initialized; }

    private:
        bool init_sdl();
        void cleanup();

        bool initialized = false;

        SDL_WindowUPtr _window{nullptr, SDL_DestroyWindow};
        SDL_RendererSPtr _renderer{nullptr};
};

using WindowUPtr = std::unique_ptr<Window>;
