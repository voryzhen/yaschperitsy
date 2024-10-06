#pragma once

#include "IRendererImpl.hpp"
#include "ResourceManager/IStorageGetter.hpp"
#include <SDL_render.h>
#include <SDL_video.h>
#include <cstddef>
#include <string_view>

class SDLWindowWrapper
{
    public:
        int width { 0 };
        int height { 0 };
        std::string_view title { "" };
        SDL_Window* sdl_window;
};

class SDLRendererWrapper
{
    public:
        static SDLRendererWrapper& get()
        {
            static SDLRendererWrapper ren_wrap;
            return ren_wrap;
        };
        SDL_Renderer* sdl_renderer { nullptr };
};

class RendererImpl : public IRendererImpl
{
    public:
        RendererImpl();
        ErrorCode initialize() override;
        ErrorCode finalize() override;

        ErrorCode clear() const override;
        ErrorCode render(const RenderData& data) const override;
        ErrorCode present() const override;

        std::pair<int, int> get_window_size() const override;

    private:
        SDLWindowWrapper _window;
        SDLRendererWrapper& _renderer;
        IStorageGetterPtr _storage;
};
