#include "resource_manager.h"
#include "SDL_ttf.h"

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <string_view>
#include <utility>

// Textures filepaths

static constexpr std::string_view player_asset{"assets/player.png"};
static constexpr std::string_view player_bullet_asset{
    "assets/playerBullet.png"};

static constexpr std::string_view enemy_asset{"assets/enemy.png"};
static constexpr std::string_view enemy_bullet_asset{
    "assets/enemyBullet.png"};

static constexpr std::string_view background_asset{
    "assets/background.png"};

// Font filepath

static constexpr std::string_view font_asset{"assets/lazy.ttf"};

//

const auto texture_deleter = [](Texture* t) -> void
{ SDL_DestroyTexture(t->_texture); };

ResourceManager::ResourceManager(const renderer_type& renderer)
    : _renderer(renderer)
{
    _textures.insert(
        {"player", std::shared_ptr<Texture>(
                       new Texture(load_texture(player_asset)),
                       texture_deleter)});

    _textures.insert(
        {"player_bullet",
         std::shared_ptr<Texture>(
             new Texture(load_texture(player_bullet_asset)),
             texture_deleter)});

    _textures.insert(
        {"enemy",
         std::shared_ptr<Texture>(
             new Texture(load_texture(enemy_asset)), texture_deleter)});

    _textures.insert({"enemy_bullet",
                      std::shared_ptr<Texture>(
                          new Texture(load_texture(enemy_bullet_asset)),
                          texture_deleter)});

    _textures.insert(
        {"background", std::shared_ptr<Texture>(
                           new Texture(load_texture(background_asset)),
                           texture_deleter)});

    _fonts.insert(std::make_pair<std::string_view, TTF_Font*>(
        "lazy", load_font(font_asset)));
}

ResourceManager::~ResourceManager()
{
    for (auto& [name, font] : _fonts)
    {
        TTF_CloseFont(font);
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

    auto font = TTF_OpenFont(font_asset.data(), 28);

    if (font == nullptr)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n",
               TTF_GetError());
    }
    return font;
}

std::shared_ptr<Texture>
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

TTF_Font*
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
