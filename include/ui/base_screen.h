#pragma once

#include "SDL_events.h"
#include <memory>
#include <resource_manager.h>

class BaseScreen
{
    public:
        BaseScreen(const ResourceManagerUPtr& rm,
                   const SDL_RendererSPtr& _renderer,
                   int* current_screen);
        virtual ~BaseScreen();
        virtual void update(const SDL_Event& event);
        virtual void render();
        virtual void handle_events(const SDL_Event& event);

    protected:
        int* _current_screen{nullptr};
        const ResourceManagerUPtr& _rm;
        const SDL_RendererSPtr& _renderer;
};

using BaseScreenUPtr = std::unique_ptr<BaseScreen>;