#include <core/App.hpp>

#include <core/Logger.hpp>
#include <core/events/AppEvent.hpp>
#include <core/input/Input.hpp>
#include <memory>

namespace yaschperitsy::core
{

App::App()
{
    logging::Logger::init();

    _window = std::make_unique<Window>();

    if (_window != nullptr)
    {
        _window->set_event_callback(
            [this](const events::EventSPtr& event)
            { on_event(event); });
    }
}

void App::on_event(const events::EventSPtr& event)
{
    events::EventDispatcher dispatcher(event);

    dispatcher.dispatch<events::WindowCloseEvent>(
        [this](const events::WindowCloseEventSPtr& event)
        { return on_window_close(event); });

    for (auto& it : _layer_stack)
    {
        if (event->is_handled())
        {
            break;
        }
        it->on_event(event);
    }
}

bool App::on_window_close(const events::WindowCloseEventSPtr&
                          /*event*/)
{
    _running = false;
    return true;
}

void App::run_app()
{

    logging::Logger::get_logger()->info("Runned");

    while (_running)
    {
        SDL_SetRenderDrawColor(_window->renderer().get(), 0, 0, 0, 255);
        SDL_RenderClear(_window->renderer().get());

        for (auto& layer : _layer_stack)
        {
            layer->on_update(_window->renderer());
        }
        _window->update();

        SDL_RenderPresent(_window->renderer().get());
    }
}

}; // namespace yaschperitsy::core
