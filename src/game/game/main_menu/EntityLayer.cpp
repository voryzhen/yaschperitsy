#include "EntityLayer.hpp"
#include "game/game/Assets.hpp"

namespace yaschperitsy::game::ui::main_menu
{

void EntityLayer::render(SDL_Renderer* ren)
{
    SDL_RenderCopyEx(ren, assets::Assets::player().get(), &src, &dest, 0,
                     nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

void EntityLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
}

}; // namespace yaschperitsy::game::ui::main_menu
