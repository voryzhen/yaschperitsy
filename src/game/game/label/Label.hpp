#pragma once

#include "SDL_pixels.h"
#include "core/renderer/Renderer.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include "game/game/Assets.hpp"
#include <string_view>

namespace yaschperitsy::game::ui
{

class Label
{
    public:
        Label(int x, int y, std::string_view text)
            : _lbl(yaschperitsy::core::resources::ResourceManager::
                       create_font_texture(text, assets::Assets::font(),
                                           color_free),
                   x, y)
        {
        }

        ~Label() = default;

        SDL_Color color_free = {250, 250, 200, 255};

        core::resources::TextureDrawable _lbl;

        void render(const core::renderer::SDLRendererUPtr& ren);
};

}; // namespace yaschperitsy::game::ui
