#pragma once

#include "SDL_render.h"
#include "core/Window.hpp"
#include <memory>

namespace yaschperitsy::core::renderer
{

using SDLRendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Renderer
{
    public:
        static bool init(const SDLWindowUPtr& window);

        static SDLRendererUPtr& renderer() { return _renderer; }

        static void clear() { _renderer.reset(nullptr); }

        static void prepare_scene();
        static void present_scene();

    private:
        static SDLRendererUPtr _renderer;
};

using RendererUPtr = std::unique_ptr<Renderer>;

}; // namespace yaschperitsy::core::renderer
