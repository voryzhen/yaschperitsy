#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include "Resource.h"
#include "ResourceLoader.h"
#include "core/Logger.h"
// #include "core/ResourceManager.h"

#include "SDL_pixels.h"
#include "SDL_render.h"

namespace yaschperitsy::resource_management
{

class ResourceManager;
using ResourceManagerSPtr = std::shared_ptr<ResourceManager>;

class ResourceManager
{
    public:
        static void init();

        inline static ResourceManagerSPtr& get_rm() { return _rm; }

        template <typename T, typename TLoader, typename... TArgs>
        static std::shared_ptr<T> load(const std::string_view& name,
                                       TArgs&&... args)
        {
            _store[name] = TLoader::load(std::forward<TArgs>(args)...);
            return std::static_pointer_cast<T>(_store[name]);
        }

    private:
        static ResourceManagerSPtr _rm;
        static std::unordered_map<std::string_view, ResourceSPtr>
            _store;
};

}; // namespace yaschperitsy::resource_management

// #include <memory>
// #include <string_view>
// #include <unordered_map>

// #include <SDL_render.h>
// #include <SDL_ttf.h>

// namespace yaschperitsy::resource2
// {

// using ResourceMap =
//     std::unordered_map<std::string_view, std::string_view>;

// struct ButtonTextures
// {
//         TextureSPtr normal;
//         TextureSPtr on_hover;
// };

// using TexturesMap = std::unordered_map<std::string_view,
// TextureSPtr>; using ButtonTexturesMap =
//     std::unordered_map<std::string_view, ButtonTextures>;
// using FontsMap = std::unordered_map<std::string_view, TTF_FontSPtr>;

// class ResourceManager
// {
//     public:
//         ResourceManager(const SDL_RendererUPtr& renderer);

//         bool load_textures(const ResourceMap& textures_info);
//         bool load_fonts(const ResourceMap& fonts_info);

//         ~ResourceManager() = default;

//         TextureSPtr get_texture(const std::string_view& texture)
//         const;

//         ButtonTextures
//         get_button_texture(const std::string_view& texture) const;
//         TTF_FontSPtr get_font(const std::string_view& font) const;

//     private:
//         const SDL_RendererUPtr& _renderer;

//         SDL_Texture* load_texture(const std::string_view& filename);
//         TTF_Font* load_font(const std::string_view& filename);

//         void init_buttons(const TTF_FontSPtr& font);

//         TexturesMap _textures;
//         ButtonTexturesMap _button_textures;
//         FontsMap _fonts;
// };

// using ResourceManagerUPtr = std::unique_ptr<ResourceManager>;

// }; // namespace yaschperitsy::resource2
