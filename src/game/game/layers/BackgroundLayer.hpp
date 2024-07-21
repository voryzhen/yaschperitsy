#pragma once

#include "SDL_rect.h"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/Layer.hpp"
#include "game/game/Assets.hpp"

namespace yaschperitsy::game::layers
{

class BackgroundImage
{
    public:
        void render(const core::renderer::SDLRendererUPtr& ren)
        {
            SDL_RenderCopyEx(ren.get(), _texture.get(), &src, &dest, 0, nullptr,
                             SDL_RendererFlip::SDL_FLIP_NONE);
        }

    private:
        core::resources::TextureSPtr _texture{
            assets::Assets::texture("background")};

        SDL_Rect src{0, 0, 1280, 720};
        SDL_Rect dest{0, 0, 1280, 720};
};

class BackgroundLayer : public yaschperitsy::core::Layer
{
    public:
        void render(const core::renderer::SDLRendererUPtr&) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        BackgroundImage _background;
};

}; // namespace yaschperitsy::game::layers
