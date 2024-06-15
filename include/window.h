#pragma once

#include <memory>
#include <string_view>

#include <SDL_render.h>

using SDL_WindowUPtr =
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

using SDL_RendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Window
{
    public:
        Window();
        ~Window();

        Window(const Window&) = delete;
        Window(const Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(const Window&&) = delete;

        SDL_RendererUPtr& get_renderer() { return _renderer; }

        bool is_initialized() const { return initialized; }

    private:
        bool init_sdl();
        void cleanup();

        bool initialized = false;

        SDL_WindowUPtr _window{nullptr, SDL_DestroyWindow};
        SDL_RendererUPtr _renderer{nullptr, SDL_DestroyRenderer};
};

using WindowUPtr = std::unique_ptr<Window>;
