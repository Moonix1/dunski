#include "window.h"

namespace Duski {

	Window::Window(int width, int height)
        : m_Width(width), m_Height(height) {
        WNDCLASS wc = { sizeof(WNDCLASS) };
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"MyOpenGLWindow";
        RegisterClass(&wc);

        HWND hwnd = CreateWindow(wc.lpszClassName, L"OpenGL Framebuffer",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            nullptr, nullptr, wc.hInstance, nullptr);
        m_HDC = GetDC(hwnd);
	}

}