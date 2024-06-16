#pragma once

#include <ecs2/components/transform_component.h>
#include <ecs2/entity.h>
#include <ecs2/icomponent.h>
#include <memory>

namespace yaschperitsy::ecs2::components
{

class KeyboardController : public IComponent
{
    public:
        void init() override
        {
            _transform_component =
                owner->get_component<TransformComponent>();
        }

        void update(const SDL_Event& e) override
        {
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                case SDLK_w:
                    _transform_component->set_y_velocity(-1.f);
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    _transform_component->set_x_velocity(-1.f);
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    _transform_component->set_y_velocity(1.f);
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    _transform_component->set_x_velocity(1.f);
                    break;
                default:
                    break;
                }
            }
            if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                case SDLK_w:
                    _transform_component->set_y_velocity(.0f);
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    _transform_component->set_x_velocity(.0f);
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    _transform_component->set_y_velocity(.0f);
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    _transform_component->set_x_velocity(.0f);
                    break;
                default:
                    break;
                }
            }
            // TODO: refactor, very - very
            {
                auto pos = _transform_component->position();
                auto vel = _transform_component->velocity();

                if (pos.x() + 3 * vel.x() < 0 ||
                    pos.x() + 3 * vel.x() > 1230)
                {
                    _transform_component->set_x_velocity(.0f);
                }

                if (pos.y() + 3 * vel.y() < 0 ||
                    pos.y() + 3 * vel.y() > 670)
                {
                    _transform_component->set_y_velocity(.0f);
                }
            }
        }

    private:
        TransformComponentSPtr _transform_component;
};

}; // namespace yaschperitsy::ecs2::components
