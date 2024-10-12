#include "utils.hpp"

#include "app_event.hpp"
#include "mouse_event.hpp"
#include "key_event.hpp"

#include "window.hpp"
#include "console_manager.hpp"

#include <windowsx.h>
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

    m_Data = new WindowData();
    m_Data->Width = width;
    m_Data->Height = height;
    m_Data->BorderWidth = 5;

    HWND hwnd = CreateWindowEx(0, TEXT("WNDCLASS"), TEXT("OpenGL"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, m_Data);

    if (!hwnd)
    {
        delete m_Data;

        std::string err_message = ConsoleManager::get_instance().push_error("[Window] Failed to create window");
        show_message_box(err_message, "Error", MB_OK | MB_ICONERROR);

        exit(EXIT_FAILURE);
    }
    
    m_HDC = GetDC(hwnd);
    set_pixel_format(m_HDC);

    m_GLContext = wglCreateContext(m_HDC);
    wglMakeCurrent(m_HDC, m_GLContext);

    if (!gladLoadGL())
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_GLContext);
        DeleteDC(m_HDC);

        delete m_Data;

        std::string err_message = ConsoleManager::get_instance().push_error("[Window] Failed to initialize GLAD");
        show_message_box(err_message, "Error", MB_OK | MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    // enable dark mode
    BOOL use_dark_mode = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &use_dark_mode, sizeof(use_dark_mode));

    // enable shadow
    DWMNCRENDERINGPOLICY ncrp = DWMNCRP_ENABLED;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));

    ConsoleManager::get_instance().push_info("Window '{}' Created {} {}", title, width, height);

    ShowWindow(hwnd, nCmdShow);

    m_MSG = {};
}

Window::~Window()
{
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_GLContext);
    DeleteDC(m_HDC);

    delete m_Data;
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

void Window::set_event_callback(const std::function<void(Event &)> &callback)
{
    m_Data->EventCallback = callback;
}

HWND Window::get_hwnd() const
{
    return m_HWND;
}

void Window::show_message_box(const std::string &message, const std::string &caption, long mode)
{
    std::wstring msg = string_to_wstring(message);
    std::wstring cpt = string_to_wstring(caption);
    MessageBox(nullptr, msg.c_str(), cpt.c_str(), mode);
}

LRESULT CALLBACK Window::window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WindowData *userData = (WindowData *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (uMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
        WindowData *pData = (WindowData *)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pData);

        pData->BorderBrush = CreateSolidBrush(RGB(255, 0, 0));

        // redraw_frame(hwnd);
        break;
    }
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        if (userData->EventCallback)
        {
            WindowResizeEvent event(width, height);
            userData->EventCallback(event);
        }
        
        return 0;
    }
    case WM_DESTROY:
    {
        DeleteObject(userData->BorderBrush);
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

void Window::redraw_frame(HWND hwnd)
{
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
}
