#ifndef WIN32CPP_CONTROL_H
#define WIN32CPP_CONTROL_H

#include "types.h"

// C++
#include <functional>
#include <map>

namespace win32cpp
{
    class Control
    {
    public:
        using Callback = std::function<LRESULT(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)>;

        explicit Control(tstring tstrClassName, HINSTANCE hInstance, HWND hWndParent) : m_tstrClassName(tstrClassName), m_hInst(hInstance), m_hWndParent(hWndParent) {}
        virtual ~Control() = default;

        // Register window class for after use
        ATOM Register();

        // Add Message Handler
        void On(UINT message, Callback onFunc);

        // Create control
        bool Create();

        // Get handle
        HWND Handle() { return m_hWnd; }

    private:
        static ATOM m_atom;

        tstring m_tstrClassName{};

        HINSTANCE m_hInst{};
        HWND m_hWndParent{};
        HWND m_hWnd{};
        std::map<UINT, Callback> m_mapMsgHandler{};

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        // Control is MDI window
        static bool IsMdi(HWND hWnd);
    };
} // win32cpp

#endif // WIN32CPP_CONTROL_H
