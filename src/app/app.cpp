#include <app/app.h>

namespace yaschperitsy::app
{

App::App()
{
    _window = std::make_unique<Window>();
    if (_window->is_initialized())
    {
        _resource_manager = std::make_unique<resource::ResourceManager>(
            _window->get_renderer());
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
    switch (_event.type)
    {
    case SDL_QUIT:
        _running = false;
    default:
        break;
    }
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
    SDL_RenderClear(_window->get_renderer().get());
    _screen_manager->render(_window->get_renderer());
    SDL_RenderPresent(_window->get_renderer().get());
}

} // namespace yaschperitsy::app
