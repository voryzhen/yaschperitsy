#pragma once

#include <string_view>
#include <utility>

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "core/Logger.h"
#include "core/Window.h"
#include "core/resource_management/Resource.h"

namespace yaschperitsy::ui
{

class UIButton
{
    public:
        UIButton() = default;

        UIButton(int x, int y, const std::string_view& name,
                 resource_management::TextureSPtr free_texture,
                 resource_management::TextureSPtr pressed_texture,
                 resource_management::TextureSPtr hover_texture)
            : _name(name), _free_texture(std::move(free_texture)),
              _pressed_texture(std::move(pressed_texture)),
              _hover_texture(std::move(hover_texture)),
              _curr_texture(_free_texture)
        {
            _free_texture->set_pos(x, y);
            _pressed_texture->set_pos(x, y);
            _hover_texture->set_pos(x, y);
            _curr_texture->set_pos(x, y);
            _geom = _curr_texture->geom();
        }

        void render(const core::SDL_RendererUPtr& ren)
        {
            _curr_texture->render(ren);
        }

        bool is_hover() const { return _hovered; }

        bool is_pressed() const { return _pressed; }

        void on_hover()
        {
            _hovered = true;
            _curr_texture =
                _pressed ? _pressed_texture : _hover_texture;
        }

        void on_loose_focus()
        {
            _hovered = false;
            _curr_texture = _free_texture;
        }

        void on_pressed()
        {
            _pressed = true;
            _curr_texture = _pressed_texture;
            core::logging::Logger::get_logger()->info(
                "{0} button pressed. Do callback", _name);
        }

        void on_released()
        {
            _pressed = false;
            _curr_texture = _hovered ? _hover_texture : _free_texture;
        }

        bool intersect(int x_pos, int y_pos) const
        {
            if (x_pos < _geom.x || x_pos > _geom.x + _geom.w)
            {
                return false;
            }
            if (y_pos < _geom.y || y_pos > _geom.y + _geom.h)
            {
                return false;
            }
            return true;
        }

    private:
        bool _hovered = false;
        bool _pressed = false;

        std::string_view _name;

        SDL_Rect _geom{};

        resource_management::TextureSPtr _free_texture;
        resource_management::TextureSPtr _pressed_texture;
        resource_management::TextureSPtr _hover_texture;
        resource_management::TextureSPtr _curr_texture;
};

}; // namespace yaschperitsy::ui
