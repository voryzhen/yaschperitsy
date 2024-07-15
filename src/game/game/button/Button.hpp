#pragma once

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "core/events/Event.hpp"
#include "core/events/MouseEvent.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include <array>
#include <string_view>

namespace yaschperitsy::game::ui
{

using EventCallbackFn =
    std::function<void(const yaschperitsy::core::events::EventSPtr&)>;

class Button
{
    public:
        Button(int x, int y, int w, int h, std::string_view text, int code)
            : _code(code)
        {
            _font = yaschperitsy::core::resources::ResourceManager::load_font(
                "assets/fonts/alegreya.ttf", 40);

            _btn_textures[0] = yaschperitsy::core::resources::ResourceManager::
                create_font_texture(text, _font, color_free);
            _btn_textures[1] = yaschperitsy::core::resources::ResourceManager::
                create_font_texture(text, _font, color_pressed);
            _btn_textures[2] = yaschperitsy::core::resources::ResourceManager::
                create_font_texture(text, _font, color_hover);

            _btn = _btn_textures[0];

            dest = {x, y, w, h};

            SDL_QueryTexture(_btn, nullptr, nullptr, &rect.w, &rect.h);

            dest.w = rect.w;
            dest.h = rect.h;
        }

        ~Button()
        {
            SDL_DestroyTexture(_btn_textures[0]);
            SDL_DestroyTexture(_btn_textures[1]);
            SDL_DestroyTexture(_btn_textures[2]);

            TTF_CloseFont(_font);
        }

        SDL_Rect rect{};
        SDL_Rect dest{};

        SDL_Color color_free = {50, 50, 100, 255};
        SDL_Color color_pressed = {0, 150, 100, 255};
        SDL_Color color_hover = {150, 0, 100, 255};

        SDL_Texture* _btn{nullptr};
        // free pressed hover
        std::array<SDL_Texture*, 3> _btn_textures{nullptr, nullptr, nullptr};

        TTF_Font* _font{nullptr};

        void render(SDL_Renderer* ren);

        void on_event(const yaschperitsy::core::events::EventSPtr& event);

        void set_event_callback(const EventCallbackFn& callback)
        {
            _event_callback = callback;
        };

    private:
        bool _is_pressed{false};
        bool _is_hover{false};
        EventCallbackFn _event_callback;

        bool hover(const core::events::MouseMovedEventSPtr& e);
        bool click(const core::events::MouseButtonPressedEventSPtr& e);
        bool released(const core::events::MouseButtonReleasedEventSPtr& e);

        bool is_intersect(int x, int y) const;

        int _code{0};
};

}; // namespace yaschperitsy::game::ui
