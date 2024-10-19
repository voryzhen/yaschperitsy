#pragma once

// #include "ResourceManager/ResourceLoader.hpp"
#include "IOSystem/Types.hpp"
#include "IStorageSetter.hpp"
#include <string_view>
#include <unordered_map>

using ResourceMap = std::unordered_map<std::string_view, int>;

class ResourceManager
{
    public:
        static ResourceManager& get();

        ErrorCode initialize();
        ErrorCode finalize();

        RenderData load_texture(std::string_view filename) const;
        RenderData load_texture(std::string_view text, Color color) const;
        int load_font(std::string_view filename, int ptsize) const;
        RenderData update_texture(int id, std::string_view text,
                                  Color color) const;

    private:
        ResourceManager();

        IStorageSetterPtr _storage;

        // ResourceLoader &res_loader;
};
