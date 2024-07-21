#pragma once

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
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
            : _lbl_textures(yaschperitsy::core::resources::ResourceManager::
                                create_font_texture(
                                    text, assets::Assets::font(), color_free))
        {
            dest = {x, y, 0, 0};

            SDL_QueryTexture(_lbl_textures.get(), nullptr, nullptr, &rect.w,
                             &rect.h);

            dest.w = rect.w;
            dest.h = rect.h;
        }

        ~Label() = default;

        SDL_Rect rect{};
        SDL_Rect dest{};

        SDL_Color color_free = {250, 250, 200, 255};

        // free pressed hover
        core::resources::TextureUPtr _lbl_textures;

        void render(const core::renderer::SDLRendererUPtr& ren);
};

}; // namespace yaschperitsy::game::ui
