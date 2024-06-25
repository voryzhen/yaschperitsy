#pragma once

#include "spdlog/spdlog.h"
#include <memory>

namespace yaschperitsy::app::logging
{

class Logger
{
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& get_logger()
        {
            return _yaschperitsy_logger;
        }

    private:
        static std::shared_ptr<spdlog::logger> _yaschperitsy_logger;
};

}; // namespace yaschperitsy::app::logging
