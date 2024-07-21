#pragma once

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "core/renderer/Renderer.hpp"
#include <memory>
#include <string_view>
#include <utility>

namespace yaschperitsy::core::resources
{

const auto font_deleter = [](TTF_Font* font) -> void { TTF_CloseFont(font); };
const auto texture_deleter = [](SDL_Texture* texture) -> void
{ SDL_DestroyTexture(texture); };

using FontUPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;
using TextureUPtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

using TextureSPtr = std::shared_ptr<SDL_Texture>;

class TextureDrawable
{
    public:
        TextureDrawable(core::resources::TextureSPtr texture, int x, int y)
            : _texture(std::move(texture))
        {
            SDL_QueryTexture(_texture.get(), nullptr, nullptr, &src.w, &src.h);
            dst.x = x;
            dst.y = y;
            dst.w = src.w;
            dst.h = src.h;
        }

        void render(const core::renderer::SDLRendererUPtr& ren)
        {
            SDL_RenderCopyEx(ren.get(), _texture.get(), &src, &dst, 0, nullptr,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

        SDL_Rect rect() const { return dst; }

        void set_texture(core::resources::TextureSPtr texture)
        {
            _texture = std::move(texture);
            SDL_QueryTexture(_texture.get(), nullptr, nullptr, &src.w, &src.h);
            dst.w = src.w;
            dst.h = src.h;
        }

    private:
        core::resources::TextureSPtr _texture;
        SDL_Rect src{};
        SDL_Rect dst{};
};

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
