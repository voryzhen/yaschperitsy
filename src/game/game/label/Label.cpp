#include "Label.hpp"

namespace yaschperitsy::game::ui
{

void Label::render(const core::renderer::SDLRendererUPtr& ren)
{
    _lbl.render(ren);
}

}; // namespace yaschperitsy::game::ui
