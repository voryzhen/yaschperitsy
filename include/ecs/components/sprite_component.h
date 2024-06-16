#pragma once

#include <memory>

#include <ecs/components/transform_component.h>
#include <ecs/entity.h>
#include <ecs/icomponent.h>
#include <resource_manager.h>
#include <utility/vector2D.h>

#include "SDL_render.h"
#include "SDL_timer.h"

namespace yaschperitsy::ecs::components
{

class SpriteComponent : public IComponent
{
    public:
        SpriteComponent() = default;

        SpriteComponent(resource::TextureSPtr texture)
            : _texture(std::move(texture))
        {
        }

        SpriteComponent(resource::TextureSPtr texture, int frames,
                        int speed)
            : _texture(std::move(texture)), _animated(true),
              _frames(frames), _speed(speed)
        {
        }

        void init() override
        {
            _position = owner->get_component<TransformComponent>();

            _src_rect.x = _src_rect.y = 0;

            _src_rect.h = _texture->_h;
            _src_rect.w = _texture->_w;

            _dest_rect.h = _texture->_h;
            _dest_rect.w = _texture->_w;
        }

        void update(const SDL_Event& /*e*/) override
        {
            if (_animated)
            {
                // TODO:
                // Here I should update _dest_rect as soon as I have
                // multiple sprite in one source
                // But I just will flip
                // Frames must be equals 2
                _flip = static_cast<bool>((SDL_GetTicks() / _speed) %
                                          _frames);
            }
            _dest_rect.x = static_cast<int>(_position->position().x());
            _dest_rect.y = static_cast<int>(_position->position().y());
        }

        void render(const app::SDL_RendererUPtr& renderer) override
        {
            SDL_RenderCopyEx(renderer.get(), _texture->_texture,
                             &_src_rect, &_dest_rect,
                             _position->angle(), nullptr,
                             _flip ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
        }

        SDL_Rect get_texture_rect()
        {
            Vector2D<float> pos = {};
            if (_position != nullptr)
            {
                pos = _position->position();
            }
            return {static_cast<int>(pos.x()),
                    static_cast<int>(pos.y()), _texture->_w,
                    _texture->_h};
        }

    private:
        TransformComponentSPtr _position;
        resource::TextureSPtr _texture;
        SDL_Rect _src_rect{0, 0, 0, 0};
        SDL_Rect _dest_rect{0, 0, 0, 0};

        bool _animated = false;
        bool _flip = true;
        int _frames = 2;
        int _speed = 100;
};

}; // namespace yaschperitsy::ecs::components
