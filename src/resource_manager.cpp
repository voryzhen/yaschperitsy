#include "resource_manager.h"

#include <SDL.h>
#include <SDL_image.h>

static constexpr std::string_view player_asset{"assets/player.png"};
static constexpr std::string_view player_bullet_asset{
    "assets/playerBullet.png"};

static constexpr std::string_view enemy_asset{"assets/enemy.png"};
static constexpr std::string_view enemy_bullet_asset{
    "assets/enemyBullet.png"};

static constexpr std::string_view background_asset{
    "assets/background.png"};

static constexpr std::string_view font_asset{"assets/lazy.ttf"};

ResourceManager::ResourceManager(SDL_Renderer* renderer)
    : _renderer(renderer), _font(TTF_OpenFont(font_asset.data(), 28))
{
    _textures.insert(std::make_pair<std::string, SDL_Texture*>(
        std::string{"player"}, load_texture(player_asset)));
    _textures.insert(std::make_pair<std::string, SDL_Texture*>(
        std::string{"player_bullet"},
        load_texture(player_bullet_asset)));
    _textures.insert(std::make_pair<std::string, SDL_Texture*>(
        std::string{"enemy"}, load_texture(enemy_asset)));
    _textures.insert(std::make_pair<std::string, SDL_Texture*>(
        std::string{"enemy_bullet"}, load_texture(enemy_bullet_asset)));

    _textures.insert(std::make_pair<std::string, SDL_Texture*>(
        std::string{"background"}, load_texture(background_asset)));

    // Open the font
    if (_font == nullptr)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n",
               TTF_GetError());
    }
}

ResourceManager::~ResourceManager()
{
    for (auto& [name, texture] : _textures)
    {
        SDL_DestroyTexture(texture._texture);
    }
    TTF_CloseFont(_font);
}

SDL_Texture*
ResourceManager::load_texture(const std::string_view& filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Loading %s", filename.begin());

    return IMG_LoadTexture(_renderer, filename.data());
}

Texture ResourceManager::get_texture(const std::string& texture) const
{
    auto txtr = _textures.find(texture);
    if (txtr != _textures.end())
    {
        return txtr->second;
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Can not find loaded texture %s", texture.c_str());

    return nullptr;
}

TTF_Font* ResourceManager::get_font() { return _font; }
