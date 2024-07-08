#include <core/Logger.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace yaschperitsy::core::logging
{

std::shared_ptr<spdlog::logger> Logger::_yaschperitsy_logger;

void Logger::init()
{
    spdlog::set_pattern("%^[%D %T] %n: %v%$");
    _yaschperitsy_logger = spdlog::stdout_color_mt("yaschperitsy");
    _yaschperitsy_logger->set_level(spdlog::level::trace);
}

}; // namespace yaschperitsy::core::logging
