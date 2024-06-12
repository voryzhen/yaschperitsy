#pragma once

#include <iostream>
#include <memory>
#include <string_view>
#include <unordered_map>

#include "SDL_render.h"
#include "SDL_ttf.h"

using SDL_RendererSPtr =
    std::shared_ptr<SDL_Renderer>; //, decltype(&SDL_DestroyRenderer)>;

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

class ResourceManager
{
    public:
        ResourceManager(const SDL_RendererSPtr& renderer);

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager(const ResourceManager&&) = delete;
        ResourceManager& operator=(const ResourceManager&&) = delete;

        ~ResourceManager() = default;

        TextureSPtr get_texture(const std::string_view& texture) const;
        TTF_FontSPtr get_font(const std::string_view& font) const;

    private:
        const SDL_RendererSPtr& _renderer;

        SDL_Texture* load_texture(const std::string_view& filename);
        TTF_Font* load_font(const std::string_view& filename);

        std::unordered_map<std::string_view, TextureSPtr> _textures;
        std::unordered_map<std::string_view, TTF_FontSPtr> _fonts;
};

using ResourceManagerUPtr = std::unique_ptr<ResourceManager>;
