#include "SDL_events.h"
#include "SDL_render.h"
#include "resource_manager.h"
#include "window.h"
#include <app.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstddef>
#include <memory>

App::App()
{
    _window = std::make_unique<Window>();
    if (_window->is_initialized())
    {
        // Initialization
        //_renderer = _window->get_renderer();
        _rm =
            std::make_unique<ResourceManager>(_window->get_renderer());
        _sm = std::make_unique<ScreenManager>(_rm);
        run_app();
    }
}

void App::run_app()
{

    Uint32 frame_start{0};
    Uint32 frame_time{0};

    unsigned char _fps = 60;
    unsigned char _frame_delay = 1000 / _fps;

    while (is_running)
    {
        frame_start = SDL_GetTicks();

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
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
    default:
        break;
    }
    _sm->handle_events(event);
}

void App::update()
{
    auto res = _sm->update(event);
    if (res == -1)
    {
        is_running = false;
    }
}

void App::render()
{
    SDL_RenderClear(_window->get_renderer().get());

    // Do your stuff
    SDL_SetRenderDrawColor(
        _window->get_renderer().get(), default_renderer_color.r,
        default_renderer_color.g, default_renderer_color.b,
        default_renderer_color.a);
    _sm->render(_window->get_renderer());
    //  Your stuff ends

    SDL_RenderPresent(_window->get_renderer().get());
}
