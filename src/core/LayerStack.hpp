#pragma once

#include <core/Layer.hpp>

#include <vector>

namespace yaschperitsy::core
{

using LayersSVector = std::vector<LayerSPtr>;

class LayerStack
{
    public:
        LayerStack() = default;
        ~LayerStack();

        void push_layer(const LayerSPtr& layer);
        void pop_layer(const LayerSPtr& layer);

        LayersSVector::iterator begin() { return _layers.begin(); }

        LayersSVector::iterator end() { return _layers.end(); }

        std::size_t size() { return _layers.size(); }

    private:
        LayersSVector _layers;
};

}; // namespace yaschperitsy::core
