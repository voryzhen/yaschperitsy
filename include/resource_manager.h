#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include "SDL_render.h"
#include "SDL_ttf.h"

using renderer_type =
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>;

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

class ResourceManager
{
    public:
        ResourceManager(const renderer_type& renderer);

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        ~ResourceManager();

        std::shared_ptr<Texture>
        get_texture(const std::string_view& texture) const;
        TTF_Font* get_font(const std::string_view& font = "lazy") const;

    private:
        SDL_Texture* load_texture(const std::string_view& filename);
        static TTF_Font* load_font(const std::string_view& filename);

        const renderer_type& _renderer;
        std::unordered_map<std::string_view, std::shared_ptr<Texture>>
            _textures;
        std::unordered_map<std::string_view, TTF_Font*> _fonts;
};
