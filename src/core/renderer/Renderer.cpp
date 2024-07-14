#include "Renderer.hpp"
#include "SDL_render.h"
#include "core/scene/Scene.hpp"
#include <core/Logger.hpp>

namespace yaschperitsy::core::renderer
{

namespace
{
constexpr int _renderer_flags{SDL_RENDERER_ACCELERATED};
};

Renderer::Renderer(const SDLWindowUPtr& window)
{
    _renderer.reset(SDL_CreateRenderer(window.get(), -1, _renderer_flags));

    if (_renderer == nullptr)
    {
        logging::Logger::get_logger()->error(
            "Couldn't create renderer. Error: {0}", SDL_GetError());
    }

    SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);
}

Renderer::~Renderer() { SDL_DestroyRenderer(_renderer.get()); }

void Renderer::prepare_scene()
{
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(_renderer.get());
}

void Renderer::render_scene(const SceneSPtr& scene)
{
    scene->render(_renderer.get());
}

void Renderer::present_scene() { SDL_RenderPresent(_renderer.get()); }

}; // namespace yaschperitsy::core::renderer
