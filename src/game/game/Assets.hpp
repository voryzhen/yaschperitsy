#pragma once

#include "core/resource_manager/ResourceManager.hpp"

namespace yaschperitsy::game::assets
{

class Assets
{
    public:
        static void init()
        {
            _font = core::resources::ResourceManager::load_font(
                "assets/fonts/alegreya.ttf", 40);

            _player = core::resources::ResourceManager::load_texture(
                "assets/player/player.png");
        }

        static void clean()
        {
            _font.reset(nullptr);
            _player.reset(nullptr);
        }

        static const core::resources::FontUPtr& font() { return _font; }

        static const core::resources::TextureUPtr& player() { return _player; }

    private:
        static core::resources::FontUPtr _font;
        static core::resources::TextureUPtr _player;
};

}; // namespace yaschperitsy::game::assets
