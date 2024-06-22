#pragma once

#include <memory>
#include <numbers>

#include <ecs/Entity.h>
#include <ecs/IComponent.h>
#include <ecs/components/TransformComponent.h>
#include <utility/Vector2D.h>

namespace yaschperitsy::ecs::components
{

class MouseController : public IComponent
{
    public:
        void init() override
        {
            _transform_component =
                owner->get_component<TransformComponent>();
        }

        void update(const SDL_Event& /*e*/) override
        {
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            _mouse_pos = {static_cast<float>(x), static_cast<float>(y)};

            // update angle
            auto pos = _transform_component->position();

            int dy = y - pos.y();
            int dx = x - pos.x();

            _angle = -90.0f + atan2(dy, dx) * (180 / std::numbers::pi);

            _transform_component->set_angle(_angle +
                                            static_cast<float>(90.0));

            auto d2 = dy * dy + dx * dx;
            auto d = sqrt(d2);

            auto xx = dx / d;
            auto yy = dy / d;

            _direction = Vector2D<float>(xx, yy);
            _transform_component->set_direction(_direction);
        }

        void render(const app::SDL_RendererUPtr& renderer) override {}

    private:
        TransformComponentSPtr _transform_component;
        Vector2D<float> _mouse_pos;
        Vector2D<float> _direction;
        float _angle = 0;
};

}; // namespace yaschperitsy::ecs::components
