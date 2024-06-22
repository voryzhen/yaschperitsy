#include <app/ResourceManager.h>

#include <iostream>
#include <vector>

#include <SDL_image.h>

namespace
{
// Textures and fotns info
using resource_map =
    std::unordered_map<std::string_view, std::string_view>;

const resource_map textures_info = {
    {"player", "assets/player.png"},
    {"player_bullet", "assets/playerBullet.png"},
    {"enemy", "assets/enemies/enemy_1.png"},
    {"enemy2", "assets/enemies/enemy_2.png"},
    {"enemy_bullet", "assets/enemyBullet.png"},
    {"background", "assets/background.png"}};

const resource_map fonts_info = {{"lazy", "assets/lazy.ttf"}};

// Button texture info

SDL_Color _button_text_color{0, 200, 200};
SDL_Color _button_on_hover_text_color{0, 100, 200};

const std::vector<std::string_view> button_titles = {
    "New Game", "Settings", "Exit", "Back"};

// Deleters for SDL_Texture* and TTF_Fonts*
const auto texture_deleter =
    [](yaschperitsy::resource::Texture* t) -> void
{
    SDL_DestroyTexture(t->_texture);
    delete t;
};

const auto font_deleter = [](TTF_Font* font) -> void
{ TTF_CloseFont(font); };

} // namespace

namespace yaschperitsy::resource
{

ResourceManager::ResourceManager(const SDL_RendererUPtr& renderer)
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

    for (const auto& name : button_titles)
    {
        SDL_Surface* text_surface = TTF_RenderText_Solid(
            _fonts["lazy"].get(), name.data(), _button_text_color);

        auto _texture =
            TextureSPtr(new Texture(SDL_CreateTextureFromSurface(
                            _renderer.get(), text_surface)),
                        texture_deleter);

        SDL_FreeSurface(text_surface);

        text_surface =
            TTF_RenderText_Solid(_fonts["lazy"].get(), name.data(),
                                 _button_on_hover_text_color);

        auto _texture_on_hover =
            TextureSPtr(new Texture(SDL_CreateTextureFromSurface(
                            _renderer.get(), text_surface)),
                        texture_deleter);

        SDL_FreeSurface(text_surface);

        _button_textures.insert({name, {_texture, _texture_on_hover}});
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
        std::cout << "Failed to load texture! SDL_Image Error: "
                  << TTF_GetError() << std::endl;
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
        std::cout << "Failed to load lazy font! SDL_ttf Error: "
                  << TTF_GetError() << std::endl;
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

ButtonTextures ResourceManager::get_button_texture(
    const std::string_view& texture) const
{
    auto txtr = _button_textures.find(texture);
    if (txtr != _button_textures.end())
    {
        return txtr->second;
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Can not find loaded texture %s", texture.data());

    return {};
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

}; // namespace yaschperitsy::resource
