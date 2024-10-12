#pragma once

#include "event.hpp"
#include "keycodes.hpp"

class KeyEvent : public Event
{
public:
    KeyCode get_keycode() const { return m_KeyCode; }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    KeyEvent(const KeyCode keycode)
        : m_KeyCode(keycode)
    {
    }
    KeyCode m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
        : KeyEvent(keycode), m_RepeatCount(repeatCount)
    {
    }

    u16 get_repeat_count() const { return m_RepeatCount; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << static_cast<u16>(m_KeyCode) << " (" << m_RepeatCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed);
private:
    u16 m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(const KeyCode keycode)
        : KeyEvent(keycode)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << static_cast<u16>(m_KeyCode);
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased);
};

class KeyTypedEvent : public KeyEvent
{
public:
    KeyTypedEvent(const KeyCode keycode)
        : KeyEvent(keycode)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << static_cast<u16>(m_KeyCode);
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped);
};