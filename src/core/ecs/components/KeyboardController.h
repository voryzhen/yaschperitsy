#pragma once

#include "core/ecs/components/SpriteComponent.h"
#include <core/ecs/Entity.h>
#include <core/ecs/IComponent.h>
#include <core/ecs/components/TransformComponent.h>
#include <memory>

namespace yaschperitsy::ecs::components
{

class KeyboardController : public IComponent
{
    public:
        void init() override
        {
            _transform_component =
                owner.lock()->get_component<TransformComponent>();
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

            check_borders();
        }

        void render(const core::SDL_RendererUPtr& renderer) override {};

    private:
        void check_borders()
        {
            auto pos = _transform_component->position();
            auto vel = _transform_component->velocity();
            auto next_pos = pos + vel * _transform_component->speed();

            auto ent_rect = _transform_component->owner.lock()
                                ->get_component<SpriteComponent>()
                                ->texture_rect();

            if (next_pos.x() < 0 || next_pos.x() > (1280. - ent_rect.w))
            {
                _transform_component->set_x_velocity(.0f);
            }

            if (next_pos.y() < 0 || next_pos.y() > (720. - ent_rect.h))
            {
                _transform_component->set_y_velocity(.0f);
            }
        }

        TransformComponentSPtr _transform_component;
};

}; // namespace yaschperitsy::ecs::components
