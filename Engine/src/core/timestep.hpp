#pragma once

#include <chrono>

class Timestep
{
public:
    Timestep(float time = 0.0f) : m_Time(time) {}
    operator float() const { return m_Time; }
    float Seconds() { return m_Time; }
    float MilliSeconds() { return m_Time * 1000.0f; }

    static std::string get_current_time_str()
    {
        const auto now = std::chrono::system_clock::now();
        const auto time_t_now = std::chrono::system_clock::to_time_t(now);
        const std::tm local_tm = *std::localtime(&time_t_now);

        std::ostringstream oss;
        oss << std::put_time(&local_tm, "[%H:%M:%S]");
        return oss.str();
    }
private:
    float m_Time;
};