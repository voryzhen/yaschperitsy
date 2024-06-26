#pragma once

#include "SDL_events.h"
#include "app/events/Event.h"
#include <functional>
#include <memory>

#include <SDL_render.h>

namespace yaschperitsy::app
{

struct WindowProps
{
        unsigned int _height = 0;
        unsigned int _width = 0;
        std::string_view _title = 0;
};

using SDL_WindowUPtr =
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

using SDL_RendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

using EventCallbackFn = std::function<void(events::EventSPtr)>;

class Window
{
    public:
        Window();
        ~Window();

        const SDL_RendererUPtr& renderer() const { return _renderer; }

        unsigned int width() const { return _data._width; }

        unsigned int height() const { return _data._height; }

        void set_event_callback(const EventCallbackFn& callback)
        {
            _data._event_callback = callback;
        };

        void update();

    private:
        bool init_sdl();
        bool create_window(const WindowProps& win_props);

        void process_window_resize_event();
        void process_window_close_event();
        void process_keyboard_released_event();
        void process_keyboard_pressed_event();

        struct WindowData
        {
                unsigned int _width = 0;
                unsigned int _height = 0;
                EventCallbackFn _event_callback;
        };

        WindowData _data;
        SDL_Event e;

        SDL_WindowUPtr _window{nullptr, SDL_DestroyWindow};
        SDL_RendererUPtr _renderer{nullptr, SDL_DestroyRenderer};
};

using WindowUPtr = std::unique_ptr<Window>;

} // namespace yaschperitsy::app
