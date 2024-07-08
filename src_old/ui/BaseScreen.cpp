#include "ui/BaseScreen.h"

namespace yaschperitsy::ui
{

BaseScreen::BaseScreen(const resource::ResourceManagerUPtr& rm,
                       int* current_screen)
    : _current_screen(current_screen), _rm(rm) {};

BaseScreen::~BaseScreen() {}

int BaseScreen::update() { return 0; }

void BaseScreen::handle_events(const SDL_Event& event) {}

void BaseScreen::render(const resource::SDL_RendererUPtr& _renderer) {}

}; // namespace yaschperitsy::ui
