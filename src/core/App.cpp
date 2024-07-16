#include <core/App.hpp>

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

void App::run_app()
{

    logging::Logger::get_logger()->info("Runned");

    while (_running)
    {
        // renderer::Renderer::render(_scene);
        renderer::Renderer::prepare_scene();
        _scene->render(renderer::Renderer::renderer().get());
        renderer::Renderer::present_scene();

        _window->update();
        _scene->update();
        update();
    }
}

}; // namespace yaschperitsy::core
