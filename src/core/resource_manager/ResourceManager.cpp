#include "ResourceManager.hpp"

#include "core/Logger.hpp"
#include "core/renderer/Renderer.hpp"

namespace yaschperitsy::core::resources
{

TTF_Font* ResourceManager::load_font(const std::string_view& filename,
                                     int ptsize)
{
    auto font = TTF_OpenFont(filename.data(), ptsize);

    if (font == nullptr)
    {
        core::logging::Logger::get_logger()->error(
            "Failed to load font : {0}. SDL_ttf Error: {1}", filename.data(),
            TTF_GetError());
    }
    return font;
}

SDL_Texture* ResourceManager::create_font_texture(const std::string_view& text,
                                                  TTF_Font* font,
                                                  SDL_Color color)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.data(), color);

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

    return text_texture;
}

}; // namespace yaschperitsy::core::resources
