#pragma once

#include "core/resource_manager/ResourceManager.hpp"
#include <string>
#include <unordered_map>

namespace yaschperitsy::game::assets
{

using ResourceMap =
    std::unordered_map<std::string, core::resources::TextureSPtr>;

class Assets
{
    public:
        static void init()
        {
            _font = core::resources::ResourceManager::load_font(
                "assets/fonts/alegreya.ttf", 40);

            _map.insert(
                {"player", core::resources::ResourceManager::load_texture(
                               "assets/player/player.png")});

            _map.insert({"yaschperitsa_1",
                         core::resources::ResourceManager::load_texture(
                             "assets/yaschperitsy/yaschperitsa_1.png")});

            _map.insert({"yaschperitsa_2",
                         core::resources::ResourceManager::load_texture(
                             "assets/yaschperitsy/yaschperitsa_2.png")});
        }

        static void clean()
        {
            _font.reset(nullptr);

            for (auto& [name, texture] : _map)
            {
                texture.reset();
            }
        }

        static const core::resources::FontUPtr& font() { return _font; }

        static core::resources::TextureSPtr player() { return _map["player"]; }

        static core::resources::TextureSPtr texture(const std::string& name)
        {
            return _map[name];
        }

    private:
        static core::resources::FontUPtr _font;

        static ResourceMap _map;
};

}; // namespace yaschperitsy::game::assets
