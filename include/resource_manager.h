#pragma once

#include "memory"
#include "string_view"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>

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

        Texture get_texture(const std::string& texture) const;
        TTF_Font* get_font();

    private:
        SDL_Texture* load_texture(const std::string_view& filename);

        const renderer_type& _renderer;
        std::unordered_map<std::string, Texture> _textures;
        TTF_Font* _font{nullptr};
};
