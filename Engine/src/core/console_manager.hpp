#pragma once

#include "base.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <utility>

enum class ConsoleLevel : u64
{
    Info    = BIT(0),
    Error   = BIT(1),
    Warning = BIT(2),
};

struct ConsoleMessage
{
    std::string message;
    std::string timestamp;
    ConsoleLevel level;

    ConsoleMessage() = default;
    ConsoleMessage(const std::string &msg, const std::string &ts, ConsoleLevel lvl)
        : message(msg), timestamp(ts), level(lvl)
    {
    }

    std::string level_to_str(ConsoleLevel lvl) const
    {
        switch (lvl)
        {
        case ConsoleLevel::Info: return "INFO";
        case ConsoleLevel::Error: return "ERROR";
        case ConsoleLevel::Warning: return "WARNING";
        default: return "INVALID";
        }
    }

    std::string get_formatted_message() const
    {
        std::stringstream ss;
        ss << timestamp << " [" << level_to_str(level) << "] " << message;
        return ss.str();
    }
};

class ConsoleManager
{
public:
    ConsoleManager();

    void push_message(const std::string &message, ConsoleLevel level = ConsoleLevel::Info);
    void clear_messages();

    template<typename... Args>
    std::string push_message(ConsoleLevel level, const char *format, Args&&... args)
    {
        std::string message = format_string(format, std::forward<Args>(args)...);
        push_message(message, level);
        return message;
    }

    template<typename... Args>
    std::string push_info(const char *format, Args&&... args)
    {
        std::string message = format_string(format, std::forward<Args>(args)...);
        push_message(message, ConsoleLevel::Info);
        return message;
    }

    template<typename... Args>
    std::string push_error(const char *format, Args&&... args)
    {
        std::string message = format_string(format, std::forward<Args>(args)...);
        push_message(message, ConsoleLevel::Error);
        return message;
    }

    template<typename... Args>
    std::string push_warning(const char *format, Args&&... args)
    {
        std::string message = format_string(format, std::forward<Args>(args)...);
        push_message(message, ConsoleLevel::Warning);
        return message;
    }

    const std::vector<ConsoleMessage> &get_messages() const;
    static ConsoleManager &get_instance();
private:

    template<typename... Args>
    static std::string format_string(const char *format, Args&&... args)
    {
        std::ostringstream ss;
        format_string_impl(ss, format, std::forward<Args>(args)...);
        return ss.str();
    }

    static void format_string_impl(std::ostringstream &ss, const char *format)
    {
        ss << format;
    }

    template<typename T, typename... Args>
    static void format_string_impl(std::ostringstream &ss, const char *format, T &&value, Args&&... args)
    {
        while (*format)
        {
            if (*format == '{' && *(format + 1) == '}')
            {
                ss << value;
                format_string_impl(ss, format + 2, std::forward<Args>(args)...);
                return;
            }
            ss << *format++;
        }
    }

    std::vector<ConsoleMessage> m_Messages;
};