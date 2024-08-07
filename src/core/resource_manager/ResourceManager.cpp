#include "ResourceManager.hpp"

#include "SDL_image.h"
#include "core/Logger.hpp"
#include "core/renderer/Renderer.hpp"

namespace yaschperitsy::core::resources
{

FontUPtr ResourceManager::load_font(const std::string_view& filename,
                                    int ptsize)
{
    auto font = TTF_OpenFont(filename.data(), ptsize);

    if (font == nullptr)
    {
        core::logging::Logger::get_logger()->error(
            "Failed to load font : {0}. SDL_ttf Error: {1}", filename.data(),
            TTF_GetError());
    }
    return {font, font_deleter};
}

TextureSPtr ResourceManager::load_texture(const std::string_view& filename)
{
    auto texture =
        IMG_LoadTexture(renderer::Renderer::renderer().get(), filename.data());

    if (texture == nullptr)
    {
        core::logging::Logger::get_logger()->error(
            "Failed to load texture from asset : {0}. SDL_Image Error: {1}",
            filename.data(), SDL_GetError());
    }

    return {texture, texture_deleter};
}

TextureUPtr ResourceManager::create_font_texture(const std::string_view& text,
                                                 const FontUPtr& font,
                                                 SDL_Color color)
{
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(font.get(), text.data(), color);

    if (text_surface == nullptr)
    {
        core::logging::Logger::get_logger()->error(
            "Failed to create surface. Error: {0}", SDL_GetError());
    }

    auto text_texture = SDL_CreateTextureFromSurface(
        renderer::Renderer::renderer().get(), text_surface);

    if (text_texture == nullptr)
    {
        core::logging::Logger::get_logger()->error(
            "Failed to render text. Error: {0}", SDL_GetError());
    }

    SDL_FreeSurface(text_surface);

    return {text_texture, texture_deleter};
}

}; // namespace yaschperitsy::core::resources
