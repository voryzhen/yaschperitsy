#include "SDL_rect.h"
#include "SDL_render.h"
#include "core/events/Event.hpp"
#include "core/events/MouseEvent.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/renderer/Scene.hpp"
#include "core/scene/Layer.hpp"
#include "core/scene/LayerStack.hpp"
#include <core/App.hpp>

#include <core/Logger.hpp>
#include <core/events/AppEvent.hpp>
#include <core/input/Input.hpp>
#include <memory>

namespace yaschperitsy::core
{

class ExampleLayer : public Layer
{
    public:
        SDL_Rect rect = {50, 50, 100, 100};
        SDL_Rect dest = {50, 50, 100, 100};
        SDL_Color color = {50, 50, 100, 255};

        void render(SDL_Renderer* ren) override
        {
            SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(ren, &rect);
        }

        void on_event(const events::EventSPtr& event) override
        {
            if (event->event_type() == events::EventType::MouseMoved)
            {
                auto e =
                    std::dynamic_pointer_cast<events::MouseMovedEvent>(event);
                color.b = e->x_pos() % 255;
                color.r = e->y_pos() % 255;
            }
        }
};

App::App()
{
    logging::Logger::init();

    _window = std::make_unique<Window>();

    if (_window != nullptr)
    {
        _renderer = std::make_unique<renderer::Renderer>(_window->window());

        _window->set_event_callback([this](const events::EventSPtr& event)
                                    { on_event(event); });

        // Make example layer
        auto l = std::make_shared<ExampleLayer>();
        LayerStack layer_stack;
        layer_stack.push_layer(l);
        _scene = std::make_unique<renderer::Scene>(layer_stack);
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
        _renderer->prepare_scene();
        _renderer->render_scene(_scene); // TODO: For now
        _renderer->present_scene();

        _scene->on_update(); // TODO: unify
        _window->update();
    }
}

}; // namespace yaschperitsy::core
