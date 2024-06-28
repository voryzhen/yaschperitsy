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
}

bool ResourceManager::load_textures(const ResourceMap& textures_info)
{
    std::vector<std::string_view> missing_textures;

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
            missing_textures.push_back(name);
        }
    }

    if (missing_textures.empty())
    {
        core::logging::Logger::get_logger()->info(
            "All textures successfully loaded");
        return true;
    }
    else
    {
        std::string miss_res;
        for (const auto& res : missing_textures)
        {
            miss_res += (std::string{" "} + res.data());
        }
        core::logging::Logger::get_logger()->warn(
            "The following textures not loaded: [" + miss_res + " ]");
        return false;
    }
}

bool ResourceManager::load_fonts(const ResourceMap& fonts_info)
{
    std::vector<std::string_view> missing_fonts;

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
            missing_fonts.push_back(name);
        }
    }

    if (const auto font = _fonts["alegreya"]; font != nullptr)
    {
        init_buttons(font);
    }

    if (missing_fonts.empty())
    {
        core::logging::Logger::get_logger()->info(
            "All fonts successfully loaded");
        return true;
    }
    else
    {
        std::string miss_res;
        for (const auto& res : missing_fonts)
        {
            miss_res += (std::string{" "} + res.data());
        }
        core::logging::Logger::get_logger()->warn(
            "The following fonts not loaded: [" + miss_res + " ]");
        return false;
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
        core::logging::Logger::get_logger()->error(
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
        core::logging::Logger::get_logger()->error(
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
    core::logging::Logger::get_logger()->error(
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
    core::logging::Logger::get_logger()->error(
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

    core::logging::Logger::get_logger()->error(
        "Can't find loaded font {0}", font_name.data());

    return nullptr;
}

}; // namespace yaschperitsy::resource
