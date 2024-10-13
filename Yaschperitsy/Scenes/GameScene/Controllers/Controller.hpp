#pragma once

#include <memory>
#include <vector>

class Controller
{
    public:
        Controller() = default;
        virtual ~Controller() = default;
        virtual void update() {}

    private:
};
using ControllerPtr = std::shared_ptr<Controller>;
using ControllerArray = std::vector<ControllerPtr>;
