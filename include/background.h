#pragma once

#include <resource_manager.h>
#include <vector>

#include "SDL_render.h"

using renderer_type =
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>;

class Background
{
    public:
        Background(Texture background, int field_width,
                   int field_height)
            : _background(background), _field_width(field_width),
              _field_height(field_height)
        {
        }

        Texture get_texture() { return _background; }

        void render(const renderer_type& renderer)
        {
            SDL_Rect dest = {0, 0, _field_width, _field_height};
            SDL_RenderCopy(renderer.get(), _background._texture, NULL,
                           &dest);
            // make explosions
        }

        class Explosion
        {
            public:
                Explosion() = default;

                void set_pos(int x, int y)
                {
                    _x = x;
                    _y = y;
                }

                void set_speed(int dx, int dy)
                {
                    _dx = dx;
                    _dy = dy;
                }

                void set_color(int r, int g, int b, int a)
                {
                    _r = r;
                    _g = g;
                    _b = b;
                    _a = a;
                }

            private:
                int _x{0};
                int _y{0};
                int _dx{0};
                int _dy{0};
                int _r{0}, _g{0}, _b{0}, _a{0};
        };

    private:
        Texture _background{nullptr};
        int _field_width{0};
        int _field_height{0};
};
