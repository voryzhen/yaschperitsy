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
        }

        static const core::resources::FontUPtr& font() { return _font; }

    private:
        static core::resources::FontUPtr _font;
};

}; // namespace yaschperitsy::game::assets
