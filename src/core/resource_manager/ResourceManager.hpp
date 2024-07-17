#pragma once

#include "SDL_render.h"
#include "SDL_ttf.h"
#include <memory>
#include <string_view>

namespace yaschperitsy::core::resources
{

const auto font_deleter = [](TTF_Font* font) -> void { TTF_CloseFont(font); };
const auto texture_deleter = [](SDL_Texture* texture) -> void
{ SDL_DestroyTexture(texture); };

using FontUPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;
using TextureUPtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

using TextureSPtr = std::shared_ptr<SDL_Texture>;

class ResourceManager
{
    public:
        static FontUPtr load_font(const std::string_view& filename, int ptsize);

        static TextureSPtr load_texture(const std::string_view& filename);

        static TextureUPtr create_font_texture(const std::string_view& text,
                                               const FontUPtr& font,
                                               SDL_Color color);
};

}; // namespace yaschperitsy::core::resources
