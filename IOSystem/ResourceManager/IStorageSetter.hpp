#pragma once

#include "IOSystem/Types.hpp"
#include <memory>
#include <string_view>

class IStorageSetter
{
    public:
        virtual ~IStorageSetter() = default;
        virtual RenderData add_texture(std::string_view filename) = 0;
        virtual RenderData add_texture(std::string_view text, Color color) = 0;
        virtual RenderData update_texture(int id, std::string_view text,
                                          Color color) = 0;
        virtual int add_font(std::string_view filename, int ptsize) = 0;
};
using IStorageSetterPtr = std::shared_ptr<IStorageSetter>;

IStorageSetterPtr get_storage_setter();
