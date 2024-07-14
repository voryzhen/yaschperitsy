#include "Game.hpp"
#include "core/events/MouseEvent.hpp"

#include <core/Logger.hpp>

class ExampleLayer : public yaschperitsy::core::Layer
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

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override
        {
            if (event->event_type() ==
                yaschperitsy::core::events::EventType::MouseMoved)
            {
                auto e = std::dynamic_pointer_cast<
                    yaschperitsy::core::events::MouseMovedEvent>(event);
                color.b = e->x_pos() % 255;
                color.r = e->y_pos() % 255;
            }
        }
};

Game::Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("Game");

    // Make example layer
    auto l = std::make_shared<ExampleLayer>();
    yaschperitsy::core::LayerStack layer_stack;
    layer_stack.push_layer(l);
    auto _scene =
        std::make_unique<yaschperitsy::core::renderer::Scene>(layer_stack);
    set_scene(std::move(_scene));
}

Game::~Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("~Game");
}
