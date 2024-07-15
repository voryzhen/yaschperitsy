#pragma once

#include "SDL_rect.h"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/Layer.hpp"
#include "game/game/Assets.hpp"

namespace yaschperitsy::game::ui::main_menu // TODO: rename
{

class EntityLayer : public yaschperitsy::core::Layer
{
    public:
        EntityLayer()
        {
            dest = {50, 50, 50, 50};

            SDL_QueryTexture(assets::Assets::player().get(), nullptr, nullptr,
                             &src.w, &src.h);

            dest.w = src.w;
            dest.h = src.h;
        }

        void render(SDL_Renderer* ren) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        SDL_Rect src{};
        SDL_Rect dest{};
};

}; // namespace yaschperitsy::game::ui::main_menu
