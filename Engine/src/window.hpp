#pragma once

#include <Windows.h>
#include "types.h"

class Window
{
public:
    Window(HINSTANCE hInstance, int nCmdShow, const char *title, u32 width, u32 heigt);
    ~Window();

    bool is_looping() const;
    bool poll_events();
    void swap_buffers();

private:
    static LRESULT CALLBACK window_proc(HWND hnwd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void set_pixel_format(HDC hdc);
    
    HGLRC m_GLContext;
    MSG m_MSG;
    HDC m_HDC;
    HWND m_HWND;
};