#include "Label.hpp"

namespace yaschperitsy::game::ui
{

void Label::render(const core::renderer::SDLRendererUPtr& ren)
{
    SDL_RenderCopyEx(ren.get(), _lbl_textures.get(), &rect, &dest, 0, nullptr,
                     SDL_RendererFlip::SDL_FLIP_NONE);
}

}; // namespace yaschperitsy::game::ui
