#pragma once

#include <memory>
#include <resource_manager.h>

class BaseScreen
{
    public:
        BaseScreen(TTF_FontSPtr font, const SDL_RendererSPtr& _renderer,
                   int* current_screen);
        virtual ~BaseScreen();
        virtual void update(const SDL_Event& event);
        virtual void render();

    protected:
        int* _current_screen{nullptr};
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using BaseScreenUPtr = std::unique_ptr<BaseScreen>;