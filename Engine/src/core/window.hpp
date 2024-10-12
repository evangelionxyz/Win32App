#pragma once

#include "types.h"

#include <Windows.h>
#include <string>

struct WindowData
{
    u32 Width, Height;
    HBRUSH BorderBrush;
    i32 BorderWidth = 5;
};

class Window
{
public:
    Window(HINSTANCE hInstance, i32 nCmdShow, const char *title, u32 width, u32 heigt);
    ~Window();

    bool is_looping() const;
    bool poll_events();
    void swap_buffers();

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