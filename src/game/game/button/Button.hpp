#pragma once

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "core/events/Event.hpp"
#include "core/events/MouseEvent.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include "game/game/Assets.hpp"
#include <string_view>
#include <vector>

namespace yaschperitsy::game::ui
{

using EventCallbackFn =
    std::function<void(const yaschperitsy::core::events::EventSPtr&)>;

class Button
{
    public:
        Button(int x, int y, std::string_view text, int code) : _code(code)
        {
            _btn_textures.reserve(3);
            _btn_textures.emplace_back(
                yaschperitsy::core::resources::ResourceManager::
                    create_font_texture(text, assets::Assets::font(),
                                        color_free),
                x, y);
            _btn_textures.emplace_back(
                yaschperitsy::core::resources::ResourceManager::
                    create_font_texture(text, assets::Assets::font(),
                                        color_pressed),
                x, y);
            _btn_textures.emplace_back(
                yaschperitsy::core::resources::ResourceManager::
                    create_font_texture(text, assets::Assets::font(),
                                        color_hover),
                x, y);
        }

        ~Button() = default;

        void render(const core::renderer::SDLRendererUPtr& ren);

        void on_event(const yaschperitsy::core::events::EventSPtr& event);

        void set_event_callback(const EventCallbackFn& callback)
        {
            _event_callback = callback;
        };

    private:
        SDL_Color color_free = {50, 50, 100, 255};
        SDL_Color color_pressed = {0, 150, 100, 255};
        SDL_Color color_hover = {150, 0, 100, 255};

        int texture_index = 0;
        std::vector<core::resources::TextureDrawable> _btn_textures;

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
