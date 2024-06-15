#include "ui/base_screen.h"
#include "resource_manager.h"

BaseScreen::BaseScreen(const ResourceManagerUPtr& rm,
                       const SDL_RendererUPtr& _renderer,
                       int* current_screen)
    : _current_screen(current_screen), _rm(rm), _renderer(_renderer){};

BaseScreen::~BaseScreen() {}

void BaseScreen::update(const SDL_Event& event) {}

void BaseScreen::handle_events(const SDL_Event& event) {}

void BaseScreen::render() {}
