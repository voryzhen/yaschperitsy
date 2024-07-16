#pragma once

#include "SDL_scancode.h"
#include "core/input/Input.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include <ecs/Entity.hpp>
#include <ecs/components/IComponent.hpp>
#include <ecs/components/TransformComponent.hpp>
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

        void update(const SDL_Event& /*e*/) override
        {
            float x_vel = is_left() ? -1.f : (is_right() ? 1.f : 0.f);
            _transform_component->set_x_velocity(x_vel);

            float y_vel = is_up() ? -1.f : (is_down() ? 1.f : 0.f);
            _transform_component->set_y_velocity(y_vel);

            check_borders();
        }

        void render(const core::renderer::SDLRendererUPtr& renderer) override {
        };

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

        static bool is_left()
        {
            return core::input::Input::is_key_pressed(SDL_SCANCODE_LEFT) ||
                   core::input::Input::is_key_pressed(SDL_SCANCODE_A);
        }

        static bool is_right()
        {
            return core::input::Input::is_key_pressed(SDL_SCANCODE_RIGHT) ||
                   core::input::Input::is_key_pressed(SDL_SCANCODE_D);
        }

        static bool is_down()
        {
            return core::input::Input::is_key_pressed(SDL_SCANCODE_DOWN) ||
                   core::input::Input::is_key_pressed(SDL_SCANCODE_S);
        }

        static bool is_up()
        {
            return core::input::Input::is_key_pressed(SDL_SCANCODE_UP) ||
                   core::input::Input::is_key_pressed(SDL_SCANCODE_W);
        }

        TransformComponentSPtr _transform_component;
};

}; // namespace yaschperitsy::ecs::components
