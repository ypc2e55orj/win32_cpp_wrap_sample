#include "win32cpp/types.h"
#include "win32cpp/control.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    win32cpp::Control root(_T("test_control"), hInstance, nullptr);
    root.Register();
    root.Create();

    win32cpp::Control control1(_T("test_control"), hInstance, root.Handle());
    control1.On(WM_CREATE, [&](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
        MessageBox(hWnd, _T("WM_CREATE"), _T("WM_CREATE"), MB_OK);

        return 0;
    });
    control1.Create();

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
