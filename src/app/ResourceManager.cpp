#include <app/ResourceManager.h>

#include "Logger.h"
#include "SDL_error.h"

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include <SDL_image.h>

namespace
{
// Textures and fotns info
using resource_map =
    std::unordered_map<std::string_view, std::string_view>;

const resource_map textures_info = {
    // clang-format off
    {"player"        , "assets/player/player.png"},
    {"player_bullet" , "assets/player/player_bullet.png"},

    {"yaschperitsa_1"        , "assets/yaschperitsy/yaschperitsa_1.png"},
    {"yaschperitsa_2"        , "assets/yaschperitsy/yaschperitsa_2.png"},
    {"yaschperitsy_fireball" , "assets/yaschperitsy/yaschperitsy_fireball.png"},

    {"background" , "assets/background.png"}
    // clang-format on
};

const resource_map fonts_info = {
    {"alegreya", "assets/fonts/alegreya.ttf"}};

// Button texture info

SDL_Color _button_text_color{0, 200, 200};
SDL_Color _button_on_hover_text_color{0, 100, 200};

// TODO: Refactor - add label class
const std::vector<std::string_view> button_titles = {
    "New Game", "Settings", "Exit", "Back", "Reset", "You win"};

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
    std::vector<std::string_view> missing_resources;

    for (const auto& [name, path] : textures_info)
    {
        auto texture_ptr = load_texture(path);
        if (texture_ptr != nullptr)
        {
            _textures.insert(
                {name, TextureSPtr(new Texture(texture_ptr),
                                   texture_deleter)});
        }
        else
        {
            missing_resources.push_back(name);
        }
    }

    for (const auto& [name, path] : fonts_info)
    {
        auto font_ptr = load_font(path);
        if (font_ptr != nullptr)
        {
            _fonts.insert(
                {name, TTF_FontSPtr(load_font(path), font_deleter)});
        }
        else
        {
            missing_resources.push_back(name);
        }
    }

    if (const auto font = _fonts["alegreya"]; font != nullptr)
    {
        init_buttons(font);
    }

    if (missing_resources.empty())
    {
        app::logging::Logger::get_logger()->info(
            "All resources successfully loaded");
    }
    else
    {
        std::string miss_res;
        for (const auto& res : missing_resources)
        {
            miss_res += (std::string{" "} + res.data());
        }
        app::logging::Logger::get_logger()->warn(
            "Some resources not loaded: [" + miss_res + " ]");
    }
}

void ResourceManager::init_buttons(const TTF_FontSPtr& font)
{
    for (const auto& name : button_titles)
    {
        SDL_Surface* text_surface = TTF_RenderText_Solid(
            font.get(), name.data(), _button_text_color);

        auto _texture =
            TextureSPtr(new Texture(SDL_CreateTextureFromSurface(
                            _renderer.get(), text_surface)),
                        texture_deleter);

        SDL_FreeSurface(text_surface);

        text_surface = TTF_RenderText_Solid(
            font.get(), name.data(), _button_on_hover_text_color);

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
    auto texture = IMG_LoadTexture(_renderer.get(), filename.data());

    if (texture == nullptr)
    {
        app::logging::Logger::get_logger()->error(
            "Failed to load texture from asset : {0}. SDL_Image Error: "
            "{1}",
            filename.data(), SDL_GetError());
    }

    return texture;
}

TTF_Font* ResourceManager::load_font(const std::string_view& filename)
{
    auto font = TTF_OpenFont(filename.data(), 28);

    if (font == nullptr)
    {
        app::logging::Logger::get_logger()->error(
            "Failed to load font : {0}. SDL_ttf Error: {1}",
            filename.data(), TTF_GetError());
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
    app::logging::Logger::get_logger()->error(
        "Can't find loaded texture {0}", texture.data());

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
    app::logging::Logger::get_logger()->error(
        "Can't find loaded button's texture {0}", texture.data());

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

    app::logging::Logger::get_logger()->error(
        "Can't find loaded font {0}", font_name.data());

    return nullptr;
}

}; // namespace yaschperitsy::resource
