#pragma once

#include <app/ResourceManager.h>
#include <ecs/Entity.h>
#include <ecs/IComponent.h>
#include <ecs/components/TransformComponent.h>

#include "SDL_render.h"

namespace yaschperitsy::ecs::components
{

class SpriteComponent : public IComponent
{
    public:
        SpriteComponent() = default;

        SpriteComponent(resource::TextureSPtr texture)
            : _texture(std::move(texture))
        {
            set_rects();
        }

        SpriteComponent(resource::TextureSPtr texture, int frames,
                        int speed)
            : _texture(std::move(texture)), _animated(true),
              _frames(frames), _speed(speed)
        {
            set_rects();
        }

        void set_sprite_settings(int frames, int speed)
        {
            _animated = true;
            _frames = frames;
            _speed = speed;
        }

        void init() override
        {
            _position =
                owner.lock()->get_component<TransformComponent>();
        }

        void update(const SDL_Event& /*e*/) override
        {
            if (_animated)
            {
                // TODO:
                // Here I should update _dest_rect as soon as I have
                // multiple sprite in one source
                // But now I just vertically flip one texture
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

        SDL_Rect texture_rect()
        {
            auto pos = _position->position();
            return {static_cast<int>(pos.x()),
                    static_cast<int>(pos.y()), _texture->_w,
                    _texture->_h};
        }

    private:
        void set_rects()
        {
            _src_rect.h = _texture->_h;
            _src_rect.w = _texture->_w;
            _dest_rect.h = _texture->_h;
            _dest_rect.w = _texture->_w;
        }

        TransformComponentSPtr _position;
        resource::TextureSPtr _texture;
        SDL_Rect _src_rect{0, 0, 0, 0};
        SDL_Rect _dest_rect{0, 0, 0, 0};

        // Sprite settings
        bool _animated = false;
        bool _flip = true;
        int _frames = 2;
        int _speed = 100;
};

}; // namespace yaschperitsy::ecs::components
