#pragma once

#include <utility>
#include <vector>

#include "SDL_rect.h"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/Layer.hpp"
#include "game/game/Assets.hpp"

namespace yaschperitsy::game::layers
{

class Entity
{
    public:
        Entity(core::resources::TextureSPtr texture, int x, int y)
            : _texture(std::move(texture))
        {
            dest = {x, y, 50, 50};

            SDL_QueryTexture(_texture.get(), nullptr, nullptr, &src.w, &src.h);

            dest.w = src.w;
            dest.h = src.h;
        }

        void render(SDL_Renderer* ren)
        {
            SDL_RenderCopyEx(ren, _texture.get(), &src, &dest, 0, nullptr,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

        core::resources::TextureSPtr _texture;
        SDL_Rect src{};
        SDL_Rect dest{};
};

class EntityLayer : public yaschperitsy::core::Layer
{
    public:
        EntityLayer()
        {
            _entities.emplace_back(assets::Assets::player(), 50, 50);
            _entities.emplace_back(assets::Assets::texture("yaschperitsa_1"),
                                   250, 50);
            _entities.emplace_back(assets::Assets::texture("yaschperitsa_2"),
                                   450, 50);

            _entities.emplace_back(assets::Assets::texture("player_bullet"),
                                   650, 50);

            _entities.emplace_back(assets::Assets::texture("fireball"), 850,
                                   50);
        }

        void render(SDL_Renderer* ren) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        std::vector<Entity> _entities;
};

}; // namespace yaschperitsy::game::layers
