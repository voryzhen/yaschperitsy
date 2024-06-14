#include "SDL_events.h"
#include "SDL_render.h"
#include "resource_manager.h"
#include "ui/screen_manager.h"
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
        _renderer = _window->get_renderer();
        _rm = std::make_unique<ResourceManager>(_renderer);
        _sm = std::make_unique<ScreenManager>(_rm->get_font("lazy"),
                                              _renderer);

        // Run app
        run_app();

        // std::make_unique<Game>(SCREEN_WIDTH,
        // SCREEN_HEIGHT, _renderer,
        //                        _rm)
        //     ->run_game();
    }
}

void App::run_app()
{
    while (is_running)
    {
        handle_events();
        update();
        render();
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
    SDL_RenderClear(_renderer.get());

    // Do your stuff
    SDL_SetRenderDrawColor(_renderer.get(), default_renderer_color.r,
                           default_renderer_color.g,
                           default_renderer_color.b,
                           default_renderer_color.a);
    _sm->render();
    //  Your stuff ends

    SDL_RenderPresent(_renderer.get());
}
