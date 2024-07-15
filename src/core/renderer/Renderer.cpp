#include "Renderer.hpp"
#include "SDL_render.h"
#include "core/scene/Scene.hpp"
#include <core/Logger.hpp>

namespace yaschperitsy::core::renderer
{

SDLRendererUPtr Renderer::_renderer{nullptr, SDL_DestroyRenderer};

namespace
{
constexpr int _renderer_flags{SDL_RENDERER_ACCELERATED};
};

bool Renderer::init(const SDLWindowUPtr& window)
{
    _renderer.reset(SDL_CreateRenderer(window.get(), -1, _renderer_flags));

    if (_renderer == nullptr)
    {
        logging::Logger::get_logger()->error(
            "Couldn't create renderer. Error: {0}", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);
    return true;
}

void Renderer::render(const SceneSPtr& scene)
{
    prepare_scene();
    scene->render(_renderer.get());
    present_scene();
}

void Renderer::prepare_scene()
{
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(_renderer.get());
}

void Renderer::present_scene() { SDL_RenderPresent(_renderer.get()); }

}; // namespace yaschperitsy::core::renderer
