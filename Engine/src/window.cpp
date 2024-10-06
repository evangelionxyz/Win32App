#include "window.hpp"

#include <dwmapi.h>
#include <glad/glad.h>

#include <iostream>

Window::Window(HINSTANCE hInstance, int nCmdShow, const char *title, u32 width, u32 height)
{
    WNDCLASS wc = {};
    wc.lpszClassName = TEXT("WNDCLASS");
    wc.lpfnWndProc = window_proc;
    wc.hInstance = hInstance;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, TEXT("WNDCLASS"), TEXT("OpenGL"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd)
    {
        MessageBox(hwnd, TEXT("Failed to create window"), 
            TEXT("Failed to create window"), MB_OK);
        __debugbreak();
    }

    BOOL use_dark_mode = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &use_dark_mode, sizeof(use_dark_mode));

    m_HDC = GetDC(hwnd);
    set_pixel_format(m_HDC);

    m_GLContext = wglCreateContext(m_HDC);
    wglMakeCurrent(m_HDC, m_GLContext);

    if (!gladLoadGL())
        std::cerr << "Failed to initialize GLAD" << std::endl;

    ShowWindow(hwnd, nCmdShow);

    m_MSG = {};
}

Window::~Window()
{
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_GLContext);
    DeleteDC(m_HDC);
}

bool Window::is_looping() const
{
    return m_MSG.message != WM_QUIT;
}

bool Window::poll_events()
{
    if (PeekMessage(&m_MSG, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&m_MSG);
        DispatchMessage(&m_MSG);
        return true;
    }
    return false;
}

void Window::swap_buffers()
{
    SwapBuffers(m_HDC);
}

LRESULT CALLBACK Window::window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Window::set_pixel_format(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, format, &pfd);
}