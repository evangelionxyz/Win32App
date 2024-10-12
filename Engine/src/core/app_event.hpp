#pragma once

#include "event.hpp"

#include <filesystem>

class WindowResizeEvent : public Event
{
private:
    u32 m_Width, m_Height;
public:
    WindowResizeEvent(u32 width, u32 height)
        : m_Width(width), m_Height(height)
    {
    }

    inline u32 get_width() const { return m_Width; }
    inline u32 get_height() const { return m_Height; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    };

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() { }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "WindowCloseEvent: Window Closed!";
        return ss.str();
    };

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class FramebufferResizeEvent : public Event
{
private:
    int m_Width, m_Height;
public:
    FramebufferResizeEvent(i32 width, i32 height)
        : m_Width(width), m_Height(height)
    {
    }

    inline i32 get_width() const { return m_Width; }
    inline i32 get_height() const { return m_Height; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "FramebufferResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(FramebufferResize);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppTickEvent : public Event
{
public:
    AppTickEvent() { }
    EVENT_CLASS_TYPE(AppTick);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppUpdateEvent : public Event
{
public:
    AppUpdateEvent() { }
    EVENT_CLASS_TYPE(AppUpdate);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppRenderEvent : public Event
{
public:
    AppRenderEvent() { }
    EVENT_CLASS_TYPE(AppRender);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class WindowDropEvent : public Event
{
public:
    WindowDropEvent(const std::vector<std::filesystem::path> &paths)
        : m_Paths(paths)
    {
    }
    WindowDropEvent(std::vector<std::filesystem::path> &&paths)
        : m_Paths(std::move(paths))
    {
    }

    const std::vector<std::filesystem::path> &get_paths() const { return m_Paths; }

    EVENT_CLASS_TYPE(WindowDrop);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);

private:
    std::vector<std::filesystem::path> m_Paths;
};
