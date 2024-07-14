#pragma once

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "core/renderer/Renderer.hpp"
#include <string_view>

namespace yaschperitsy::core::resources
{

class ResourceManager
{

    public:
        static TTF_Font* load_font(const std::string_view& filename,
                                   int ptsize);

        static SDL_Texture* create_font_texture(const std::string_view& text,
                                                TTF_Font* font,
                                                SDL_Color color);
};

}; // namespace yaschperitsy::core::resources
