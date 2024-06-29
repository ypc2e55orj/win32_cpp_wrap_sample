#include "control.h"

namespace win32cpp
{
    ATOM Control::m_atom = 0;

    LRESULT CALLBACK Control::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        Control *pThis = nullptr;
        if (message == WM_CREATE)
        {
            pThis = reinterpret_cast<Control *>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
            LONG_PTR lpPrevUserData = SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
            if (lpPrevUserData != 0)
            {
                // TODO: malform
            }
        }
        else
        {
            pThis = reinterpret_cast<Control*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            if (!pThis)
            {
                // TODO: Window is not created (WM_GETMINMAXINFO, etc...)
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }

        auto itMsgHandler = pThis->m_mapMsgHandler.find(message);
        if (itMsgHandler != pThis->m_mapMsgHandler.end())
        {
            return itMsgHandler->second(hWnd, message, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        // TODO: ref count to exit application
    }

    bool Control::IsMdi(HWND hWnd)
    {
        WINDOWINFO winInfo{};
        if (GetWindowInfo(hWnd, &winInfo) == FALSE)
        {
            // TODO: error
        }
        return winInfo.dwExStyle == WS_EX_MDICHILD;
    }

    ATOM Control::Register()
    {
        if (m_atom != 0)
        {
            return m_atom;
        }

        WNDCLASSEX wcex{};

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = m_hInst;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszClassName = m_tstrClassName.c_str();

        m_atom = RegisterClassEx(&wcex);
        return m_atom;
    }

    void Control::On(UINT message, Callback onFunc)
    {
        // TODO: Mutex
        m_mapMsgHandler[message] = onFunc;
    }

    bool Control::Create()
    {
        m_hWnd = CreateWindowEx(
            0,
            m_tstrClassName.c_str(),
            m_tstrClassName.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
            nullptr, nullptr, m_hInst,
            this);

        ShowWindow(m_hWnd, SW_SHOW);
        UpdateWindow(m_hWnd);

        return m_hWnd == NULL;
    }
}
