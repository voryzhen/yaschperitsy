#include "resource_manager.h"
#include "SDL_ttf.h"

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace
{

// Textures and fotns info
using resource_map =
    std::unordered_map<std::string_view, std::string_view>;

const resource_map textures_info = {
    {"player", "assets/player.png"},
    {"player_bullet", "assets/playerBullet.png"},
    {"enemy", "assets/enemy.png"},
    {"enemy_bullet", "assets/enemyBullet.png"},
    {"background", "assets/background.png"}};

const resource_map fonts_info = {{"lazy", "assets/lazy.ttf"}};

// Deleters for SDL_Texture* and TTF_Fonts*
const auto texture_deleter = [](Texture* t) -> void
{
    SDL_DestroyTexture(t->_texture);
    delete t;
};

const auto font_deleter = [](TTF_Font* font) -> void
{ TTF_CloseFont(font); };

} // namespace

ResourceManager::ResourceManager(const SDL_RendererPtr& renderer)
    : _renderer(renderer)
{
    for (const auto& [name, path] : textures_info)
    {
        _textures.insert(
            {name, TextureSPtr(new Texture(load_texture(path)),
                               texture_deleter)});
    }

    for (const auto& [name, path] : fonts_info)
    {
        _fonts.insert(
            {name, TTF_FontSPtr(load_font(path), font_deleter)});
    }
}

SDL_Texture*
ResourceManager::load_texture(const std::string_view& filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Loading %s", filename.begin());

    auto texture = IMG_LoadTexture(_renderer.get(), filename.data());

    if (texture == nullptr)
    {
        printf("Failed to load texture! SDL_Image Error: %s\n",
               TTF_GetError());
    }
    return texture;
}

TTF_Font* ResourceManager::load_font(const std::string_view& filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Loading %s", filename.begin());

    auto font = TTF_OpenFont(filename.data(), 28);

    if (font == nullptr)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n",
               TTF_GetError());
    }
    return font;
}

TextureSPtr
ResourceManager::get_texture(const std::string_view& texture) const
{
    auto txtr = _textures.find(texture);
    if (txtr != _textures.end())
    {
        return txtr->second;
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Can not find loaded texture %s", texture.data());

    return nullptr;
}

TTF_FontSPtr
ResourceManager::get_font(const std::string_view& font_name) const
{
    auto font = _fonts.find(font_name);
    if (font != _fonts.end())
    {
        return font->second;
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Can not find loaded font %s", font_name.data());
    return nullptr;
}
