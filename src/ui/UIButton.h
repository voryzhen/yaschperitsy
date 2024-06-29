#pragma once

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "core/Window.h"

namespace yaschperitsy::ui
{

class UIButton
{
    public:
        UIButton() = default;

        UIButton(SDL_Rect button_geom, SDL_Color button_color)
            : UIButton(button_geom, button_color, button_color,
                       button_color)
        {
        }

        UIButton(SDL_Rect button_geom, SDL_Color button_color,
                 SDL_Color hover_color, SDL_Color pressed_color)
            : _geom(button_geom), _button_current_color(button_color),
              _button_free_color(button_color),
              _button_pressed_color(pressed_color),
              _button_hover_color(hover_color)
        {
        }

        void set_geom(SDL_Rect geom) { _geom = geom; }

        void set_color(SDL_Color clr) { _button_current_color = clr; }

        void set_colors(SDL_Color clr, SDL_Color hclr, SDL_Color pclr)
        {
            _button_current_color = clr;
            _button_free_color = clr;

            _button_hover_color = hclr;
            _button_pressed_color = pclr;
        }

        void render(const core::SDL_RendererUPtr& ren)
        {
            SDL_SetRenderDrawColor(ren.get(), _button_current_color.r,
                                   _button_current_color.g,
                                   _button_current_color.b,
                                   _button_current_color.a);
            SDL_RenderFillRect(ren.get(), &_geom);
        }

        bool is_hover() const { return _hovered; }

        bool is_pressed() const { return _pressed; }

        void on_hover()
        {
            _hovered = true;
            _button_current_color =
                _pressed ? _button_pressed_color : _button_hover_color;
        }

        void on_loose_focus()
        {
            _hovered = false;
            _button_current_color = _button_free_color;
        }

        void on_pressed()
        {
            _pressed = true;
            _button_current_color = _button_pressed_color;
        }

        void on_released()
        {
            _pressed = false;
            _button_current_color =
                _hovered ? _button_hover_color : _button_free_color;
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

        SDL_Rect _geom{0, 0, 0, 0};
        SDL_Color _button_current_color{0, 0, 0, 0};
        SDL_Color _button_free_color{0, 0, 0, 0};
        SDL_Color _button_pressed_color{0, 0, 0, 0};
        SDL_Color _button_hover_color{0, 0, 0, 0};
};

}; // namespace yaschperitsy::ui
