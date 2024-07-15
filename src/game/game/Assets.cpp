#include "Assets.hpp"
#include "core/resource_manager/ResourceManager.hpp"

namespace yaschperitsy::game::assets
{

core::resources::FontUPtr Assets::_font{nullptr, core::resources::font_deleter};

};
