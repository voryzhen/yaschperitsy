#include "SDL_events.h"
#include "SDL_rect.h"
#include <array>
#include <memory>
#include <resource_manager.h>
#include <string_view>

class Button
{
    public:
        Button() = default;

        Button(const TTF_FontSPtr& font, const std::string_view& text,
               const SDL_RendererPtr& renderer, int x = 0, int y = 0)
        {
            SDL_Surface* text_surface = TTF_RenderText_Solid(
                font.get(), text.data(), _text_color);

            // TODO: rewrite text_texture creation logic
            _texture =
                std::make_shared<Texture>(SDL_CreateTextureFromSurface(
                    renderer.get(), text_surface));
            srect = {0, 0, _texture->_w, _texture->_h};
            drect = {x, y, srect.w, srect.h};
            SDL_FreeSurface(text_surface);
        }

        Button(const Button&) = default;
        // Button(const Button&&) = default;

        ~Button() = default;

        void update()
        {
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            SDL_Rect mouse_rect = {x, y, 1, 1};
            if (SDL_HasIntersection(&drect, &mouse_rect) != 0u)
            {
                std::cout << "btn clicked" << std::endl;
            }
            else
            {
                std::cout << "btn not clicked" << std::endl;
            }
        }

        void draw();

        // private:
        TextureSPtr _texture; // TODO: make a texture creator with
        // deleter in shared_ptr
        SDL_Rect srect{}, drect{};
        bool is_selected{false};
        SDL_Color _text_color{0, 200, 200};
};

class Menu
{
    public:
        Menu(const SDL_RendererPtr& renderer,
             const ResourceManagerPtr& rm)
            : _renderer{renderer}, _rm(rm)
        {
            int i = 0;
            for (const auto txt : {"Game", "Exit"})
            {
                btns[i++] = Button(_rm->get_font("lazy"), txt,
                                   _renderer, 40, 40 * (i + 1));
            }
        }

        void show_menu();
        void render();
        void render_menu();

        void update();

        // TODO: make common
        void render_text(const SDL_RendererPtr& renderer,
                         const std::string& text, int x, int y);
        void handle_events();

    private:
        const SDL_RendererPtr& _renderer;
        const ResourceManagerPtr& _rm;
        bool _quit = false;
        SDL_Event _event{};
        SDL_Color _text_color{0, 200, 200};
        std::array<Button, 2> btns;
        std::array<std::string_view, 2> _menu_items = {"Game", "Exit"};
};
