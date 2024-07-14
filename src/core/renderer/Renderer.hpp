#pragma once

#include "SDL_render.h"
#include "core/Window.hpp"
#include "core/scene/Scene.hpp"
#include <memory>

namespace yaschperitsy::core::renderer
{

using SDLRendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Renderer
{
    public:
        Renderer(const SDLWindowUPtr& window);
        ~Renderer();

        const SDLRendererUPtr& sdl_renderer() const { return _renderer; }

        void prepare_scene();
        void render_scene(const SceneSPtr& scene);
        void present_scene();

    private:
        SDLRendererUPtr _renderer{nullptr, SDL_DestroyRenderer};
};

using RendererUPtr = std::unique_ptr<Renderer>;

}; // namespace yaschperitsy::core::renderer
