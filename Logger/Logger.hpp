#pragma once

#include <chrono>
#include <format>
#include <iostream>
#include <source_location>
#include <string_view>

constexpr std::string_view RESET = "\033[0m";    /* Reset color */
constexpr std::string_view BLACK = "\033[30m";   /* Black */
constexpr std::string_view RED = "\033[31m";     /* Red */
constexpr std::string_view GREEN = "\033[32m";   /* Green */
constexpr std::string_view YELLOW = "\033[33m";  /* Yellow */
constexpr std::string_view BLUE = "\033[34m";    /* Blue */
constexpr std::string_view MAGENTA = "\033[35m"; /* Magenta */
constexpr std::string_view CYAN = "\033[36m";    /* Cyan */
constexpr std::string_view WHITE = "\033[37m";   /* White */

class Logger
{
    public:
        Logger(std::source_location location = std::source_location::current())
            : _location(location)
        {
        }

        template <typename... Args>
        void info(std::format_string<Args...> s, Args&&... args)
        {
            const auto& msg = std::format(s, std::forward<Args>(args)...);
            colored_print(GREEN, msg);
        }

        template <typename... Args>
        void error(std::format_string<Args...> s, Args&&... args)
        {
            const auto& msg = std::format(s, std::forward<Args>(args)...);
            const auto& msg_path = std::format(
                "Error:\nFile : {}\nFunction : {}\nLine : {}\nMessage : {}",
                _location.file_name(), _location.function_name(),
                _location.line(), msg);
            colored_print(RED, msg_path);
        }

    private:
        void colored_print(const std::string_view& color,
                           const std::string_view& msg)
        {
            std::cout << color << "[ " << std::chrono::system_clock::now()
                      << " ] " << msg << RESET << std::endl;
        }

        std::source_location _location;
};
