#pragma once

#include "ResourceManager/IStorageGetter.hpp"
#include "Types.hpp"

#include "IStorageGetter.hpp"
#include "IStorageSetter.hpp"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <memory>
#include <string_view>
#include <unordered_map>

using TextureMap = std::unordered_map<int, SDL_Texture*>;
using FontMap = std::unordered_map<int, TTF_Font*>;

class Storage : public IStorageSetter, public IStorageGetter
{
    public:
        RenderData add_texture(std::string_view filename) override;
        RenderData add_texture(std::string_view text, Color color) override;
        RenderData update_texture(int id, std::string_view text,
                                  Color color) override;
        int add_font(std::string_view filename, int ptsize) override;

        SDL_Texture* get_texture(int id) override;
        ErrorCode finalize() override;

    private:
        TextureMap _textures;
        FontMap _fonts;
};
using StoragePtr = std::shared_ptr<Storage>;
