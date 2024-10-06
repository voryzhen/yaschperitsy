#pragma once

#include "Component.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Entity.hpp"
#include "GraphicEngine/Types.hpp"
#include "Logger/Logger.hpp"
#include "Utility/Vector.hpp"

class SpriteComponent : public Component
{
    public:
        explicit SpriteComponent(const RenderData& ren_data)
            : render_data_(ren_data)
        {
        }

        void events() override {}

        void update() override
        {
            auto pos = transf_comp_->position();
            render_data_.x = static_cast<int>(pos.x);
            render_data_.y = static_cast<int>(pos.y);
            render_data_.angle = transf_comp_->view_direction().angle();
        }

        void render(const Renderer& ren) override { ren.render(render_data_); }

        void on_event() override {}

        void init() override
        {
            transf_comp_ = owner_.lock()->get_component<TransformComponent>();
            if (!transf_comp_)
            {
                Logger().error("Wrong components init. Transform should be "
                               "init before Sprite");
            }
            auto pos = transf_comp_->position();
            render_data_.x = pos.x;
            render_data_.y = pos.y;
            render_data_.angle = transf_comp_->view_direction().angle();
        }

        void set_render_data(const RenderData& ren_data)
        {
            render_data_ = ren_data;
        }

        RenderData render_data() const { return render_data_; }

    private:
        RenderData render_data_;
        TransformComponentPtr transf_comp_;
};
using SpriteComponentPtr = std::shared_ptr<SpriteComponent>;

////======

// SpriteComponent() = default;

//     SpriteComponent(core::resources::TextureSPtr texture)
//         : _texture(std::move(texture))
//     {
//         int w = 0;
//         int h = 0;
//         SDL_QueryTexture(_texture.get(), nullptr, nullptr, &w,
//         &h); set_rects(h, w);
//     }

//     SpriteComponent(core::resources::TextureSPtr texture, int
//     frames,
//                     int speed)
//         : _texture(std::move(texture)), _animated(true),
//         _frames(frames),
//           _speed(speed)
//     {
//         int w = 0;
//         int h = 0;
//         SDL_QueryTexture(_texture.get(), nullptr, nullptr, &w,
//         &h); set_rects(h, w);
//     }

//     void set_sprite_settings(int frames, int speed)
//     {
//         _animated = true;
//         _frames = frames;
//         _speed = speed;
//     }

//     void update(const SDL_Event & /*e*/) override
//     {
//             if (_animated) {
//                 // TODO:
//                 // Here I should update _dest_rect as soon as I
//                 have
//                 // multiple sprite in one source
//                 // But now I just vertically flip one texture
//                 // Frames must be equals 2
//                 _flip =
//                     static_cast<bool>((SDL_GetTicks() / _speed) %
//                     _frames);
//         }
//         _dest_rect.x =
//         static_cast<int>(_position->position().x()); _dest_rect.y
//         = static_cast<int>(_position->position().y());
//     }

//     void render(const core::renderer::SDLRendererUPtr &renderer)
//     override
//     {
//         SDL_RenderCopyEx(renderer.get(), _texture.get(),
//         &_src_rect,
//                          &_dest_rect, _position->angle(),
//                          nullptr, _flip ? SDL_FLIP_NONE :
//                          SDL_FLIP_VERTICAL);
//     }

//     SDL_Rect texture_rect()
//     {
//         auto pos = _position->position();
//         return { static_cast<int>(pos.x()),
//         static_cast<int>(pos.y()),
//                  _src_rect.w, _src_rect.h };
//     }

// private:
//     void set_rects(int h, int w)
//     {
//         _src_rect.h = h;
//         _src_rect.w = w;
//         _dest_rect.h = h;
//         _dest_rect.w = w;
//     }

//     TransformComponentSPtr _position;
//     core::resources::TextureSPtr _texture;
//     SDL_Rect _src_rect{ 0, 0, 0, 0 };
//     SDL_Rect _dest_rect{ 0, 0, 0, 0 };

//     // Sprite settings
//     bool _animated = false;
//     bool _flip = true;
//     int _frames = 2;
//     int _speed = 100;