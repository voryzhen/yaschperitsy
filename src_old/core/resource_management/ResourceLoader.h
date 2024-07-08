#pragma once

#include "Resource.h"
#include "SDL_image.h"
#include <memory>

namespace yaschperitsy::resource_management
{

class TextureLoader
{
    public:
        static TextureSPtr load(const std::string_view& filename,
                                const core::SDL_RendererUPtr& ren)
        {
            auto texture = IMG_LoadTexture(ren.get(), filename.data());

            if (texture == nullptr)
            {
                core::logging::Logger::get_logger()->error(
                    "Failed to load texture from asset : {0}. "
                    "SDL_Image Error: "
                    "{1}",
                    filename.data(), SDL_GetError());
            }

            return {new Texture(texture), texture_deleter};
        }
};

class TextTextureLoader
{
    public:
        static TextureSPtr load(const std::string_view& text,
                                const FontSPtr& font,
                                const core::SDL_RendererUPtr& ren,
                                SDL_Color color)
        {
            SDL_Surface* text_surface =
                TTF_RenderText_Solid(font->font(), text.data(), color);

            if (text_surface == nullptr)
            {
                core::logging::Logger::get_logger()->error(
                    "Failed to create surface. Error: {0}",
                    SDL_GetError());
            }

            auto text_texture =
                SDL_CreateTextureFromSurface(ren.get(), text_surface);

            if (text_texture == nullptr)
            {
                core::logging::Logger::get_logger()->error(
                    "Failed to render text. Error: {0}",
                    SDL_GetError());
            }

            SDL_FreeSurface(text_surface);

            return {new Texture(text_texture), texture_deleter};
        }
};

class FontLoader
{
    public:
        static FontSPtr load(const std::string_view& filename,
                             int ptsize)
        {
            auto font = TTF_OpenFont(filename.data(), ptsize);

            if (font == nullptr)
            {
                core::logging::Logger::get_logger()->error(
                    "Failed to load font : {0}. SDL_ttf Error: {1}",
                    filename.data(), TTF_GetError());
            }

            return {new Font(font), font_deleter};
        }
};

}; // namespace yaschperitsy::resource_management
