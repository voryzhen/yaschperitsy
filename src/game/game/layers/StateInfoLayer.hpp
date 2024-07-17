#pragma once

#include <string>
#include <utility>

#include "SDL_render.h"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/Layer.hpp"
#include "game/game/Assets.hpp"
#include "game/game/scenes/GameSettings.hpp"

namespace yaschperitsy::game::layers
{

class TextureDrawableObject
{
    public:
        TextureDrawableObject() = default;

        TextureDrawableObject(core::resources::TextureSPtr texture, int x,
                              int y)
            : _texture(std::move(texture))
        {
            SDL_QueryTexture(_texture.get(), nullptr, nullptr, &src.w, &src.h);
            dst.x = x;
            dst.y = y;
            dst.w = src.w;
            dst.h = src.h;
        }

        void render(const core::renderer::SDLRendererUPtr& ren)
        {
            SDL_RenderCopyEx(ren.get(), _texture.get(), &src, &dst, 0, nullptr,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

    private:
        core::resources::TextureSPtr _texture;
        SDL_Rect src{};
        SDL_Rect dst{};
};

class Topbar
{
    public:
        Topbar(GameStatistic& stat) : _stat(stat) { update(); }

        void render(const core::renderer::SDLRendererUPtr& ren)
        {
            _total_score.render(ren);
            _max_score.render(ren);
            _hp.render(ren);
            _ry.render(ren);
        }

        void update()
        {
            _total_score = TextureDrawableObject(
                core::resources::ResourceManager::create_font_texture(
                    "Total Score: " + std::to_string(_stat._score),
                    assets::Assets::font(), {255, 255, 255, 255}),
                5, 5);

            _max_score = TextureDrawableObject(
                core::resources::ResourceManager::create_font_texture(
                    "Max Score: " + std::to_string(_stat._max_score),
                    assets::Assets::font(), {255, 255, 255, 255}),
                280, 5);

            _hp = TextureDrawableObject(
                core::resources::ResourceManager::create_font_texture(
                    "HP: " + std::to_string(_stat._curr_hp),
                    assets::Assets::font(), {255, 255, 255, 255}),
                560, 5);

            _ry = TextureDrawableObject(
                core::resources::ResourceManager::create_font_texture(
                    "Remaining yaschperitsy: " +
                        std::to_string(_stat._yaschperitsy_num),
                    assets::Assets::font(), {255, 255, 255, 255}),
                800, 5);
        }

    private:
        TextureDrawableObject _total_score;
        TextureDrawableObject _max_score;
        TextureDrawableObject _hp;
        TextureDrawableObject _ry;

        GameStatistic& _stat;
};

class StateInfoLayer : public yaschperitsy::core::Layer
{
    public:
        StateInfoLayer(GameStatistic& stat) : _stat(stat), _topbar(_stat) {}

        void render(const core::renderer::SDLRendererUPtr& ren) override
        {
            _topbar.render(ren);
        }

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override
        {
        }

        void update() override { _topbar.update(); }

    private:
        GameStatistic& _stat;
        Topbar _topbar;
};

}; // namespace yaschperitsy::game::layers
