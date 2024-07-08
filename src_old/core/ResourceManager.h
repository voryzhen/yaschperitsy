#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include <SDL_render.h>
#include <SDL_ttf.h>

namespace yaschperitsy::resource
{

using ResourceMap =
    std::unordered_map<std::string_view, std::string_view>;

using SDL_RendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

struct Texture
{
    public:
        Texture(SDL_Texture* texture) : _texture(texture)
        {
            SDL_QueryTexture(_texture, NULL, NULL, &_w, &_h);
        }

        SDL_Texture* _texture{nullptr};
        int _w{0};
        int _h{0};
};

using TextureSPtr = std::shared_ptr<Texture>;
using TTF_FontSPtr = std::shared_ptr<TTF_Font>;

struct ButtonTextures
{
        TextureSPtr normal;
        TextureSPtr on_hover;
};

using TexturesMap = std::unordered_map<std::string_view, TextureSPtr>;
using ButtonTexturesMap =
    std::unordered_map<std::string_view, ButtonTextures>;
using FontsMap = std::unordered_map<std::string_view, TTF_FontSPtr>;

class ResourceManager
{
    public:
        ResourceManager(const SDL_RendererUPtr& renderer);

        bool load_textures(const ResourceMap& textures_info);
        bool load_fonts(const ResourceMap& fonts_info);

        ~ResourceManager() = default;

        TextureSPtr get_texture(const std::string_view& texture) const;

        ButtonTextures
        get_button_texture(const std::string_view& texture) const;
        TTF_FontSPtr get_font(const std::string_view& font) const;

    private:
        const SDL_RendererUPtr& _renderer;

        SDL_Texture* load_texture(const std::string_view& filename);
        TTF_Font* load_font(const std::string_view& filename);

        void init_buttons(const TTF_FontSPtr& font);

        TexturesMap _textures;
        ButtonTexturesMap _button_textures;
        FontsMap _fonts;
};

using ResourceManagerUPtr = std::unique_ptr<ResourceManager>;

}; // namespace yaschperitsy::resource
