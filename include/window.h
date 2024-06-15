#pragma once

#include <memory>

#include <SDL_render.h>

namespace yaschperitsy::app
{

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

        bool is_initialized() const { return initialized; }

        const SDL_RendererUPtr& get_renderer() const
        {
            return _renderer;
        }

        int get_width() const { return _width; }

        int get_height() const { return _height; }

    private:
        bool init_sdl();

        bool initialized = false;

        int _width{0};
        int _height{0};

        SDL_WindowUPtr _window{nullptr, SDL_DestroyWindow};
        SDL_RendererUPtr _renderer{nullptr, SDL_DestroyRenderer};
};

using WindowUPtr = std::unique_ptr<Window>;

} // namespace yaschperitsy::app
