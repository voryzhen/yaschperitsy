#include <core/App.hpp>

#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "core/events/Event.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/scene/Scene.hpp"
#include <core/Logger.hpp>
#include <core/events/AppEvent.hpp>
#include <core/input/Input.hpp>

namespace yaschperitsy::core
{

App::App()
{
    logging::Logger::init();

    _window = std::make_unique<Window>();

    if (_window != nullptr)
    {
        renderer::Renderer::init(_window->window());

        _window->set_event_callback([this](const events::EventSPtr& event)
                                    { on_event(event); });

        _scene = std::make_unique<scenes::Scene>();
    }
}

void App::on_event(const events::EventSPtr& event)
{
    events::EventDispatcher dispatcher(event);

    dispatcher.dispatch<events::WindowCloseEvent>(
        [this](const events::WindowCloseEventSPtr& event)
        { return on_window_close(event); });

    if (!event->is_handled())
    {
        _scene->on_event(event);
    }
}

bool App::on_window_close(const events::WindowCloseEventSPtr&
                          /*event*/)
{
    _running = false;
    return true;
}

void App::app_update()
{
    _window->update();
    _scene->update();
    update();
}

void App::app_render()
{
    renderer::Renderer::prepare_scene();
    _scene->render(renderer::Renderer::renderer());
    renderer::Renderer::present_scene();
}

void App::run_app()
{
    logging::Logger::get_logger()->info("Runned");

    Uint32 last_time{0}; // = SDL_GetTicks();
    Uint32 delta{0};
    Uint32 tpf = 1000.0 / 60.0;

    while (_running)
    {
        last_time = SDL_GetTicks();

        app_update();
        app_render();

        delta = SDL_GetTicks() - last_time;

        if (delta < tpf)
        {
            SDL_Delay(tpf - delta);
        }
    }
}

}; // namespace yaschperitsy::core
