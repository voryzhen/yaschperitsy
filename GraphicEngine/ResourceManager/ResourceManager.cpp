#include "ResourceManager.hpp"
#include "Types.hpp"

ResourceManager& ResourceManager::get()
{
    static ResourceManager singleton;
    return singleton;
}

ResourceManager::ResourceManager() : _storage(get_storage_setter()) {}

ErrorCode ResourceManager::initialize() { return ErrorCode::NoError; }

ErrorCode ResourceManager::finalize() { return ErrorCode::NoError; }

int ResourceManager::load_font(std::string_view filename, int ptsize) const
{
    return _storage->add_font(filename, ptsize);
}

RenderData ResourceManager::load_texture(std::string_view filename) const
{
    return _storage->add_texture(filename);
}

RenderData ResourceManager::load_texture(std::string_view text,
                                         Color color) const
{
    return _storage->add_texture(text, color);
}

RenderData ResourceManager::update_texture(int id, std::string_view text,
                                           Color color) const
{
    return _storage->update_texture(id, text, color);
}
