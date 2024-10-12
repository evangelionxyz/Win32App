#pragma once

#include "event.hpp"

#include <Windows.h>
#include <string>

#include <functional>

struct WindowData
{
    u32 Width, Height;
    i32 BorderWidth = 5;
    HBRUSH BorderBrush;

    std::function<void(Event &)> EventCallback;
};

class Window
{
public:
    Window(HINSTANCE hInstance, i32 nCmdShow, const char *title, u32 width, u32 heigt);
    ~Window();

    bool is_looping() const;
    bool poll_events();
    void swap_buffers();

    void set_event_callback(const std::function<void(Event &)> &callback);

    HWND get_hwnd() const;

    static void show_message_box(const std::string &message, const std::string &caption, long mode = MB_OK);

private:
    static LRESULT CALLBACK window_proc(HWND hnwd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void set_pixel_format(HDC hdc);
    static void redraw_frame(HWND hwnd);

    WindowData *m_Data = nullptr;
    
    HGLRC m_GLContext;
    MSG m_MSG;
    HDC m_HDC;
    HWND m_HWND;
};