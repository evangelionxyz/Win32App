#include "console_manager.hpp"
#include "timestep.hpp"

static ConsoleManager *s_Instance = nullptr;

ConsoleManager::ConsoleManager()
{
    s_Instance = this;
    m_Messages.reserve(50);
}

void ConsoleManager::push_message(const std::string &message, ConsoleLevel level)
{
    if (m_Messages.size() > 1000)
        m_Messages.erase(m_Messages.begin());

    m_Messages.push_back({message, Timestep::get_current_time_str(), level});
}

void ConsoleManager::clear_messages()
{
    if (!m_Messages.empty())
        m_Messages.clear();
}

const std::vector<ConsoleMessage> &ConsoleManager::get_messages() const
{
    return m_Messages;
}

ConsoleManager &ConsoleManager::get_instance()
{
    return *s_Instance;
}
