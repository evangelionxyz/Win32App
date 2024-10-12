#pragma once

#include "base.hpp"

enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, WindowDrop,
    FramebufferResize,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type)																											\
				static EventType get_static_type() { return EventType::type; }								\
				virtual EventType get_event_type() const override { return get_static_type(); }	\
				virtual const char* get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

class Event
{
public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType get_event_type() const = 0;
    virtual const char *get_name() const = 0;
    virtual int get_category_flags() const = 0;
    virtual std::string to_string() const { return get_name(); }

    bool is_in_category(EventCategory cat)
    {
        return get_category_flags() & cat;
    }
};

class EventDispatcher
{
public:
    EventDispatcher(Event &event)
        : m_Event(event)
    {
    }

    template<typename T, typename F>
    bool dispatch(const F &func)
    {
        if (m_Event.get_event_type() == T::get_static_type())
        {
            m_Event.Handled = func(static_cast<T &>(m_Event));
            return true;
        }
        return false;
    }

private:
    Event &m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.to_string();
}
