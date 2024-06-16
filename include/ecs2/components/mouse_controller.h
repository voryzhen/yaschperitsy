#pragma once

#include <numbers>

#include <ecs2/components/transform_component.h>
#include <ecs2/entity.h>
#include <ecs2/icomponent.h>
#include <game/vector2D.h>

namespace yaschperitsy::ecs2::components
{

class MouseController : public IComponent
{
    public:
        void init() override
        {
            auto transform_component =
                owner->get_component<TransformComponent>();

            _transform_component = std::make_shared<TransformComponent>(
                transform_component.get());
        }

        void update(const SDL_Event& /*e*/) override
        {
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            _mouse_pos = {static_cast<float>(x), static_cast<float>(y)};

            // update angle
            auto pos = _transform_component->position();

            float dy = static_cast<float>(y) - pos.y();
            float dx = static_cast<float>(x) - pos.x() + 25;

            _angle = -90 + atan2(dy, dx) * (180 / std::numbers::pi);

            _transform_component->set_angle(_angle +
                                            static_cast<float>(90.0));

            float d2 = dy * dy + dx * dx;
            float d = sqrtf(d2);

            float xx = dx / d;
            float yy = dy / d;

            _direction = Vector2D(xx, yy);
            _transform_component->set_direction(_direction);
        }

        void render(const app::SDL_RendererUPtr& renderer) override {}

    private:
        TransformComponentSPtr _transform_component;
        Vector2D _mouse_pos;
        Vector2D _direction;
        float _angle = 0;
};

}; // namespace yaschperitsy::ecs2::components
