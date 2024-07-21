#pragma once

#include "SDL_pixels.h"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/Layer.hpp"
#include "game/game/Assets.hpp"
#include "game/game/scenes/GameSettings.hpp"
#include <array>

namespace yaschperitsy::game::layers
{

class Topbar
{
    public:
        Topbar(GameStatistic& stat) : _stat(stat) {}

        void render(const core::renderer::SDLRendererUPtr& ren)
        {
            _total_score.render(ren);
            _max_score.render(ren);
            _hp.render(ren);
            _ry.render(ren);
        }

        void update()
        {
            _total_score.set_texture(
                core::resources::ResourceManager::create_font_texture(
                    "Total Score: " + std::to_string(_stat._score),
                    assets::Assets::font(), _color));

            _max_score.set_texture(
                core::resources::ResourceManager::create_font_texture(
                    "Max Score: " + std::to_string(_stat._max_score),
                    assets::Assets::font(), _color));

            _hp.set_texture(
                core::resources::ResourceManager::create_font_texture(
                    "HP: " + std::to_string(_stat._curr_hp),
                    assets::Assets::font(), _color));

            _ry.set_texture(
                core::resources::ResourceManager::create_font_texture(
                    "Remaining yaschperitsy: " +
                        std::to_string(_stat._yaschperitsy_num),
                    assets::Assets::font(), _color));
        }

    private:
        SDL_Color _color = {255, 255, 255, 255};
        int _top_padding = 5;
        std::array<int, 4> _horizontal_layout = {5, 280, 560, 800};

        core::resources::TextureDrawable _total_score{
            core::resources::ResourceManager::create_font_texture(
                "Total Score: ", assets::Assets::font(), _color),
            _horizontal_layout[0], _top_padding};

        core::resources::TextureDrawable _max_score{
            core::resources::ResourceManager::create_font_texture(
                "Max Score: ", assets::Assets::font(), _color),
            _horizontal_layout[1], _top_padding};

        core::resources::TextureDrawable _hp{
            core::resources::ResourceManager::create_font_texture(
                "HP: ", assets::Assets::font(), _color),
            _horizontal_layout[2], _top_padding};

        core::resources::TextureDrawable _ry{
            core::resources::ResourceManager::create_font_texture(
                "Remaining yaschperitsy: ", assets::Assets::font(), _color),
            _horizontal_layout[3], _top_padding};

        GameStatistic& _stat;
};

class StateInfoLayer : public yaschperitsy::core::Layer
{
    public:
        StateInfoLayer(GameStatistic& stat) : _topbar(stat) {}

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
        Topbar _topbar;
};

}; // namespace yaschperitsy::game::layers
