#include <app/App.h>

#include "app/events/AppEvent.h"

namespace yaschperitsy::core
{

const resource::ResourceMap textures_info = {
    // clang-format off
    {"player"        , "assets/player/player.png"},
    {"player_bullet" , "assets/player/player_bullet.png"},

    {"yaschperitsa_1"        , "assets/yaschperitsy/yaschperitsa_1.png"},
    {"yaschperitsa_2"        , "assets/yaschperitsy/yaschperitsa_2.png"},
    {"yaschperitsy_fireball" , "assets/yaschperitsy/yaschperitsy_fireball.png"},

    {"background" , "assets/background.png"}
    // clang-format on
};

const resource::ResourceMap fonts_info = {
    {"alegreya", "assets/fonts/alegreya.ttf"}};

App::App()
{
    logging::Logger::init();

    _window = std::make_unique<Window>();

    if (_window != nullptr)
    {
        _window->set_event_callback(
            [this](const events::EventSPtr& event)
            { on_event(event); });

        _resource_manager = std::make_unique<resource::ResourceManager>(
            _window->renderer());

        _resource_manager->load_textures(textures_info);
        _resource_manager->load_fonts(fonts_info);

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

void App::on_event(const events::EventSPtr& event)
{
    logging::Logger::get_logger()->info(event->as_string());

    events::EventDispatcher dispatcher(event);

    dispatcher.dispatch<events::WindowCloseEvent>(
        [this](const events::WindowCloseEventSPtr& event)
        { return on_window_close(event); });
}

bool App::on_window_close(const events::WindowCloseEventSPtr& /*event*/)
{
    _running = false;
    return true;
}

} // namespace yaschperitsy::core
