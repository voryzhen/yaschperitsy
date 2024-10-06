#include "RendererImpl.hpp"

#include "Logger/Logger.hpp"
#include "ResourceManager/IStorageGetter.hpp"
#include "SDL_render.h"
#include "Types.hpp"
#include <SDL_rect.h>
#include <SDL_video.h>

RendererImpl::RendererImpl() : _renderer(SDLRendererWrapper::get()) {}

ErrorCode RendererImpl::initialize()
{
    int _window_flags { SDL_WINDOW_RESIZABLE };
    int _window_x_pos { SDL_WINDOWPOS_UNDEFINED };
    int _window_y_pos { SDL_WINDOWPOS_UNDEFINED };
    int _height = 720;
    int _width = 1280;
    std::string title = "Ящперицы";

    _window.sdl_window =
        SDL_CreateWindow(title.data(), _window_x_pos, _window_y_pos, _width,
                         _height, _window_flags);

    if (_window.sdl_window == nullptr)
    {
        Logger().error("Couldn't open window. Error: {0}", SDL_GetError());
        return ErrorCode::SDLWindowCreationError;
    }

    _window.height = _height;
    _window.width = _width;

    int _renderer_flags { SDL_RENDERER_ACCELERATED };

    _renderer.sdl_renderer =
        SDL_CreateRenderer(_window.sdl_window, -1, _renderer_flags);

    if (_renderer.sdl_renderer == nullptr)
    {
        Logger().error("Couldn't create renderer. Error: {0}", SDL_GetError());
        return ErrorCode::SDLRendererCreationError;
    }

    SDL_SetRenderDrawColor(_renderer.sdl_renderer, 0, 0, 0, 255);

    _storage = get_storage_getter();
    if (_storage == nullptr)
    {
        Logger().error("Couldn't get storage getter interface");
        return ErrorCode::TexturesFontsStorageInitError;
    }

    return ErrorCode::NoError;
}

ErrorCode RendererImpl::finalize()
{
    if (_storage->finalize() != ErrorCode::NoError)
    {
        return ErrorCode::TexturesFontsStoragefinalizeError;
    }
    SDL_DestroyRenderer(_renderer.sdl_renderer);
    SDL_DestroyWindow(_window.sdl_window);
    return ErrorCode::NoError;
}

ErrorCode RendererImpl::clear() const
{
    if (SDL_RenderClear(_renderer.sdl_renderer) < 0)
    {
        return ErrorCode::SDLRendererClearError;
    }
    return ErrorCode::NoError;
}

ErrorCode RendererImpl::render(const RenderData& data) const
{
    auto texture = _storage->get_texture(data.id);
    SDL_Rect src { 0, 0, data.w, data.h };
    SDL_Rect dst { data.x, data.y, data.w, data.h };
    if (SDL_RenderCopyEx(_renderer.sdl_renderer, texture, &src, &dst,
                         data.angle, nullptr, SDL_FLIP_NONE) < 0)
    {
        return ErrorCode::SDLRendererRenderError;
    }
    // 6 param center - center of rotation by angle angle (5 param)
    //_flip ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
    return ErrorCode::NoError;
}

ErrorCode RendererImpl::present() const
{
    SDL_RenderPresent(_renderer.sdl_renderer);
    return ErrorCode::NoError;
}

std::pair<int, int> RendererImpl::get_window_size() const
{
    return { _window.height, _window.width };
};

IRendererImplPtr get_renderer_impl()
{
    static IRendererImplPtr impl = std::make_shared<RendererImpl>();
    return impl;
}
