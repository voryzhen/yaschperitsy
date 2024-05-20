#pragma once

#include "string_view"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>

#include "SDL_render.h"
#include "SDL_ttf.h"

class ResourceManager
{
    public:
        ResourceManager(SDL_Renderer* renderer);

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        ~ResourceManager();

        SDL_Texture* get_texture(const std::string& texture) const;
        TTF_Font* get_font();

    private:
        SDL_Texture* load_texture(const std::string_view& filename);

        SDL_Renderer* _renderer{nullptr};
        std::unordered_map<std::string, SDL_Texture*> _textures;
        TTF_Font* _font{nullptr};
};
