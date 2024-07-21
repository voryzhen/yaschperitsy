#pragma once

#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/Layer.hpp"
#include "game/game/Assets.hpp"
#include "game/game/scenes/GameSettings.hpp"

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
            _total_score = core::resources::TextureDrawable(
                core::resources::ResourceManager::create_font_texture(
                    "Total Score: " + std::to_string(_stat._score),
                    assets::Assets::font(), {255, 255, 255, 255}),
                5, 5);

            _max_score = core::resources::TextureDrawable(
                core::resources::ResourceManager::create_font_texture(
                    "Max Score: " + std::to_string(_stat._max_score),
                    assets::Assets::font(), {255, 255, 255, 255}),
                280, 5);

            _hp = core::resources::TextureDrawable(
                core::resources::ResourceManager::create_font_texture(
                    "HP: " + std::to_string(_stat._curr_hp),
                    assets::Assets::font(), {255, 255, 255, 255}),
                560, 5);

            _ry = core::resources::TextureDrawable(
                core::resources::ResourceManager::create_font_texture(
                    "Remaining yaschperitsy: " +
                        std::to_string(_stat._yaschperitsy_num),
                    assets::Assets::font(), {255, 255, 255, 255}),
                800, 5);
        }

    private:
        core::resources::TextureDrawable _total_score{
            core::resources::ResourceManager::create_font_texture(
                "Total Score: ", assets::Assets::font(), {255, 255, 255, 255}),
            5, 5};

        core::resources::TextureDrawable _max_score{
            core::resources::ResourceManager::create_font_texture(
                "Max Score: ", assets::Assets::font(), {255, 255, 255, 255}),
            280, 5};

        core::resources::TextureDrawable _hp{
            core::resources::ResourceManager::create_font_texture(
                "HP: ", assets::Assets::font(), {255, 255, 255, 255}),
            560, 5};

        core::resources::TextureDrawable _ry{
            core::resources::ResourceManager::create_font_texture(
                "Remaining yaschperitsy: ", assets::Assets::font(),
                {255, 255, 255, 255}),
            800, 5};

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
