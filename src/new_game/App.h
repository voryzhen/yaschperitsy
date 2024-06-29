#pragma once

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "core/App.h"
#include "core/Layer.h"
#include "core/Logger.h"
#include "core/Window.h"
#include "core/events/Event.h"
#include "core/events/MouseEvent.h"
#include <memory>

namespace yaschperitsy::game
{

class UILayer : public core::Layer
{
    public:
        UILayer() : core::Layer("UI Layer") {}

        void on_update(const core::SDL_RendererUPtr& ren) override
        {
            SDL_SetRenderDrawColor(ren.get(), curr_color.r,
                                   curr_color.g, curr_color.b,
                                   curr_color.a);
            SDL_RenderFillRect(ren.get(), &r);
        }

        void on_event(const core::events::EventSPtr& event) override
        {
            core::events::EventDispatcher dispatcher(event);

            dispatcher.dispatch<core::events::MouseButtonPressedEvent>(
                [this](const core::events::MouseButtonPressedEventSPtr&
                           event)
                { return on_mouse_btn_click(event); });

            dispatcher.dispatch<core::events::MouseButtonReleasedEvent>(
                [this](const core::events::MouseButtonReleasedEventSPtr&
                           event)
                { return on_mouse_btn_released(event); });

            dispatcher.dispatch<core::events::MouseMovedEvent>(
                [this](const core::events::MouseMovedEventSPtr& event)
                { return on_mouse_btn_moved(event); });
        }

    private:
        bool on_mouse_btn_click(
            const core::events::MouseButtonPressedEventSPtr& e)
        {
            if ((abs(75 - e->y_pos()) < 25) &&
                (abs(125 - e->x_pos()) < 75))
            {
                curr_color = pressed_color;
            }

            return true;
        }

        bool on_mouse_btn_released(
            const core::events::MouseButtonReleasedEventSPtr& e)
        {
            if ((abs(75 - e->y_pos()) < 25) &&
                (abs(125 - e->x_pos()) < 75))
            {
                curr_color = free_color;
            }

            return true;
        }

        bool
        on_mouse_btn_moved(const core::events::MouseMovedEventSPtr& e)
        {
            if ((abs(75 - e->y_pos()) < 25) &&
                (abs(125 - e->x_pos()) < 75))
            {
                curr_color = hover_color;
            }
            else
            {
                curr_color = free_color;
            }

            return true;
        }

        SDL_Rect r = {50, 50, 150, 50};

        SDL_Colour curr_color = {0, 0, 255, 255};

        SDL_Colour free_color = {0, 0, 255, 255};
        SDL_Colour pressed_color = {0, 255, 0, 255};
        SDL_Colour hover_color = {255, 0, 0, 255};
};

const resource::ResourceMap textures = {
    // clang-format off
    {"player"        , "assets/player/player.png"},
    {"player_bullet" , "assets/player/player_bullet.png"},

    {"yaschperitsa_1"        , "assets/yaschperitsy/yaschperitsa_1.png"},
    {"yaschperitsa_2"        , "assets/yaschperitsy/yaschperitsa_2.png"},
    {"yaschperitsy_fireball" , "assets/yaschperitsy/yaschperitsy_fireball.png"},

    {"background" , "assets/background.png"}
    // clang-format on
};

const resource::ResourceMap fonts = {
    {"alegreya", "assets/fonts/alegreya.ttf"}};

class NewGame : public core::App
{
    public:
        NewGame()
        {
            push_layer(std::make_shared<UILayer>());
            load_assets(textures);
            load_fonts(fonts);
        }

        NewGame(bool old) : App(old) {}

        ~NewGame() {}
};

}; // namespace yaschperitsy::game
