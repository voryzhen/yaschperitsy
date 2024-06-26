#include <app/App.h>
#include <functional>
#include <utility>

#include "Logger.h"
#include "app/Window.h"
#include "app/events/Event.h"

namespace yaschperitsy::app
{

App::App()
{
    app::logging::Logger::init();

    _window = std::make_unique<Window>();

    if (_window != nullptr)
    {
        _window->set_event_callback([this](events::EventSPtr e)
                                    { on_event(std::move(e)); });

        _resource_manager = std::make_unique<resource::ResourceManager>(
            _window->renderer());
        _screen_manager =
            std::make_unique<ui::ScreenManager>(_resource_manager);
        run_app();
    }
}

void App::run_app()
{

    Uint32 frame_start{0};
    Uint32 frame_time{0};

    unsigned char _fps = 60;
    unsigned char _frame_delay = 1000 / _fps;

    while (_running)
    {
        frame_start = SDL_GetTicks();

        // New api
        _window->update();

        handle_events();
        update();
        render();

        frame_time = SDL_GetTicks() - frame_start;

        if (_frame_delay > frame_time)
        {
            SDL_Delay(_frame_delay - frame_time);
        }
    }
}

void App::handle_events()
{
    SDL_PollEvent(&_event);
    _screen_manager->handle_events(_event);
}

void App::update()
{
    auto res = _screen_manager->update();
    if (res == -1)
    {
        _running = false;
    }
}

void App::render()
{
    SDL_RenderClear(_window->renderer().get());
    _screen_manager->render(_window->renderer());
    SDL_RenderPresent(_window->renderer().get());
}

} // namespace yaschperitsy::app
