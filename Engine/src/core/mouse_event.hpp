#pragma once

#include "event.hpp"
#include "mouse_codes.hpp"

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(const f32 x, const f32 y)
        : m_MouseX(x), m_MouseY(y)
    {
    }

    f32 get_x() const { return m_MouseX; }
    f32 get_y() const { return m_MouseY; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved);
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
    f32 m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(const f32 xOffset, const f32 yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset)
    {
    }

    f32 get_x() const { return m_XOffset; }
    f32 get_y() const { return m_YOffset; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << get_x() << ", " << get_y();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled);
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
private:
    f32 m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
public:
    MouseCode get_button() const { return m_Button; }
    bool Is(MouseCode bt) { return m_Button == bt; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
    MouseButtonEvent(const MouseCode button)
        : m_Button(button)
    {
    }

    MouseCode m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(const MouseCode button)
        : MouseButtonEvent(button)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << static_cast<u16>(m_Button);
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(const MouseCode button)
        : MouseButtonEvent(button)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << static_cast<u16>(m_Button);
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased);
};