#include "ResourceStorage.hpp"
#include "Logger/Logger.hpp"
#include "RendererImpl/RendererImpl.hpp"
#include "Types.hpp"
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

namespace
{
SDL_Texture* create_sdl_texture_from_text(SDL_Renderer* ren,
                                          std::string_view text, TTF_Font* font,
                                          Color color)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(
        font, text.data(), SDL_Color { color.r, color.g, color.b, color.a });
    if (text_surface == nullptr)
    {
        Logger().error("Failed to create surface. Error: {0}", SDL_GetError());
        return nullptr;
    }

    auto text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
    if (text_texture == nullptr)
    {
        Logger().error("Failed to render text. Error: {0}", SDL_GetError());
        return nullptr;
    }
    SDL_FreeSurface(text_surface);

    return text_texture;
}
}; // namespace

RenderData Storage::add_texture(std::string_view filename)
{
    int id = _textures.size();

    // Yeah
    auto* ren = SDLRendererWrapper::get().sdl_renderer;
    auto* texture = IMG_LoadTexture(ren, filename.data());

    if (texture == nullptr)
    {
        Logger().error("Can't load texture \"{}\" Error: {}", filename.data(),
                       SDL_GetError());
        return { .x = -1, .y = -1, .w = -1, .h = -1, .id = -1 };
    }

    int w { 0 };
    int h { 0 };
    if (SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) < 0)
    {
        Logger().error("SDL_QueryTexture Error: {}", SDL_GetError());
        return { .x = -1, .y = -1, .w = -1, .h = -1, .id = -1 };
    }

    _textures.insert({ id, texture });

    return { .x = 0, .y = 0, .w = w, .h = h, .id = id };
};

RenderData Storage::add_texture(std::string_view text, Color color)
{
    auto* ren = SDLRendererWrapper::get().sdl_renderer;

    SDL_Texture* texture =
        create_sdl_texture_from_text(ren, text, _fonts[0], color);

    if (texture == nullptr)
    {
        Logger().error("Can't create texture. Error: {}", SDL_GetError());
        return { .x = -1, .y = -1, .w = -1, .h = -1, .id = -1 };
    }

    int id = _textures.size();

    int w { 0 };
    int h { 0 };
    if (SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) < 0)
    {
        Logger().error("SDL_QueryTexture Error: {}", SDL_GetError());
        return { .x = -1, .y = -1, .w = -1, .h = -1, .id = -1 };
    }

    _textures.insert({ id, texture });

    return { .x = 0, .y = 0, .w = w, .h = h, .id = id };
};

int Storage::add_font(std::string_view filename, int ptsize)
{
    auto font = TTF_OpenFont(filename.data(), ptsize);
    if (font == nullptr)
    {
        Logger().error("Can't load font \"{}\" Error: {}", filename.data(),
                       SDL_GetError());
        return -1;
    }

    int id = _fonts.size();
    _fonts.insert({ id, font });
    return id;
}

RenderData Storage::update_texture(int id, std::string_view text, Color color)
{
    auto texture = _textures.find(id);
    if (texture == _textures.end())
    {
        Logger().error("Can't find texture for update with id : {}", id);
        return { .x = 404, .y = 404, .w = 404, .h = 404, .id = id };
    }
    auto* ren = SDLRendererWrapper::get().sdl_renderer;
    auto new_texture =
        create_sdl_texture_from_text(ren, text, _fonts[0], color);
    int w { 0 };
    int h { 0 };
    if (SDL_QueryTexture(new_texture, nullptr, nullptr, &w, &h) < 0)
    {
        Logger().error("SDL_QueryTexture Error: {}", SDL_GetError());
        return { .x = -1, .y = -1, .w = -1, .h = -1, .id = -1 };
    }
    SDL_DestroyTexture(texture->second);
    texture->second = new_texture;
    return { .x = 0, .y = 0, .w = w, .h = h, .id = id };
}

ErrorCode Storage::finalize()
{
    for (auto& [k, v] : _textures)
    {
        SDL_DestroyTexture(v);
    }
    for (auto& [k, v] : _fonts)
    {
        TTF_CloseFont(v);
    }
    return ErrorCode::NoError;
}

SDL_Texture* Storage::get_texture(int id)
{
    auto texture = _textures.find(id);
    if (texture == _textures.end())
    {
        Logger().error("Can't find texture by id : {}", id);
        return nullptr;
    }
    return texture->second;
};

static StoragePtr storage = std::make_shared<Storage>();

IStorageSetterPtr get_storage_setter() { return storage; }
IStorageGetterPtr get_storage_getter() { return storage; }
