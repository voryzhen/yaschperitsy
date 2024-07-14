#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
// #include "core/ResourceManager.h"
#include "core/Logger.h"
#include "core/Window.h"

#include <memory>
#include <string_view>
#include <utility>

namespace yaschperitsy::resource_management
{

enum class ResourceType
{
    font,
    texture
};

class Resource
{
    public:
        virtual ResourceType type() const = 0;

        virtual ~Resource() {}
};

using ResourceSPtr = std::shared_ptr<Resource>;

class Texture : public Resource
{
    public:
        Texture(SDL_Texture* texture) : _texture(texture)
        {
            SDL_QueryTexture(_texture, nullptr, nullptr, &_src.w, &_src.h);
            _dst.w = _src.w;
            _dst.h = _src.h;
        }

        void render(const core::SDL_RendererUPtr& ren)
        {
            SDL_RenderCopyEx(ren.get(), _texture, &_src, &_dst, 0, nullptr,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

        static ResourceType static_type() { return ResourceType::texture; }

        virtual ResourceType type() const override { return static_type(); }

        SDL_Texture* texture() const { return _texture; }

        SDL_Rect geom() const { return _dst; }

        void set_pos(int x, int y)
        {
            _dst.x = x;
            _dst.y = y;
        }

    private:
        SDL_Texture* _texture = nullptr;
        SDL_Rect _dst{0, 0, 0, 0};
        SDL_Rect _src{0, 0, 0, 0};
};

const auto texture_deleter = [](Texture* t) -> void
{ SDL_DestroyTexture(t->texture()); };

using TextureSPtr = std::shared_ptr<Texture>;

class Font : public Resource
{
    public:
        Font(TTF_Font* font) : _font(font) {}

        TTF_Font* font() const { return _font; }

        static ResourceType static_type() { return ResourceType::font; }

        virtual ResourceType type() const override { return static_type(); }

    private:
        TTF_Font* _font = nullptr;
};

const auto font_deleter = [](Font* font) -> void
{ TTF_CloseFont(font->font()); };

using FontSPtr = std::shared_ptr<Font>;

}; // namespace yaschperitsy::resource_management
