#pragma once

#include <string>
#include <unordered_map>

#include "core/Logger.hpp"
#include "core/resource_manager/ResourceManager.hpp"

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

            // Player asset
            _map.insert(
                {"player", core::resources::ResourceManager::load_texture(
                               "assets/player/player.png")});

            // Enemies asset
            _map.insert({"yaschperitsa_1",
                         core::resources::ResourceManager::load_texture(
                             "assets/yaschperitsy/yaschperitsa_1.png")});

            _map.insert({"yaschperitsa_2",
                         core::resources::ResourceManager::load_texture(
                             "assets/yaschperitsy/yaschperitsa_2.png")});

            // Bullets asset
            _map.insert({"player_bullet",
                         core::resources::ResourceManager::load_texture(
                             "assets/player/player_bullet.png")});

            _map.insert({"fireball",
                         core::resources::ResourceManager::load_texture(
                             "assets/yaschperitsy/yaschperitsy_fireball.png")});
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
            auto texture = _map.find(name);
            if (texture != _map.end())
            {
                return texture->second;
            }
            core::logging::Logger::get_logger()->info(
                "Can't find texture with name {0}", name);
            return nullptr;
        }

    private:
        static core::resources::FontUPtr _font;

        static ResourceMap _map;
};

}; // namespace yaschperitsy::game::assets
