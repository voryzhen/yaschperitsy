#include "LayerStack.h"
#include <algorithm>

namespace yaschperitsy::core
{

LayerStack::~LayerStack()
{
    for (auto& layer : _layers)
    {
        layer->on_detach();
    }
}

void LayerStack::push_layer(const LayerSPtr& layer)
{
    _layers.emplace_back(layer);
    layer->on_attach();
}

void LayerStack::pop_layer(const LayerSPtr& layer)
{
    auto it = std::find(_layers.begin(), _layers.end(), layer);
    if (it != _layers.end())
    {
        layer->on_detach();
        _layers.erase(it);
    }
}

}; // namespace yaschperitsy::core
