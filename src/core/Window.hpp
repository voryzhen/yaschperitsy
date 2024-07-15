#pragma once

#include <memory>

#include <core/events/Event.hpp>

#include "SDL_events.h"

namespace yaschperitsy::core
{

using SDLWindowUPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

using EventCallbackFn = std::function<void(const events::EventSPtr&)>;

struct WindowProps
{
        unsigned int _height = 0;
        unsigned int _width = 0;
        std::string_view _title;
};

class Window
{
    public:
        Window();
        ~Window();

        const SDLWindowUPtr& window() const { return _window; };

        // const SDLRendererUPtr& renderer() const { return _renderer;
        // };

        unsigned int width() const { return _data._width; }

        unsigned int height() const { return _data._height; }

        void set_event_callback(const EventCallbackFn& callback)
        {
            _data._event_callback = callback;
        };

        void update();

    private:
        static bool init_sdl();
        bool create_window(const WindowProps& win_props);

        struct WindowData
        {
                unsigned int _width = 0;
                unsigned int _height = 0;
                EventCallbackFn _event_callback;
        };

        WindowData _data;

        SDL_Event e{};

        SDLWindowUPtr _window{nullptr, SDL_DestroyWindow};
};

using WindowUPtr = std::unique_ptr<Window>;

}; // namespace yaschperitsy::core
