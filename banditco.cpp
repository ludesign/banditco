#ifndef UNICODE
    #define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h> // for EXIT_ codes

// declaration of Windows Procedure callback
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(pCmdLine);

    WNDCLASSEX wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"banditco";
    wcex.hIconSm = 0;

    if (!::RegisterClassExW(&wcex)) {
        return EXIT_FAILURE;
    }

    DWORD wndStyle = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);
    DWORD wndExStyle = 0;
    RECT rect = { 0, 0, 640, 480 };
    if (!::AdjustWindowRectEx(&rect, wndStyle, TRUE, wndExStyle)) {
        return EXIT_FAILURE;
    }

    int xOffset = (::GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2;
    int yOffset = (::GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2;

    HWND hWnd = ::CreateWindowExW(0L, L"banditco", L"banditco alpha 0.01", wndStyle, xOffset, yOffset, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
    if (!hWnd) {
        return EXIT_FAILURE;
    }

    ::SetWindowPos(hWnd, HWND_TOPMOST, xOffset, yOffset, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

    BOOL bMsgFlag = 0;
    MSG pMsg = { 0 };
    while ((bMsgFlag = ::GetMessageW(&pMsg, NULL, 0, 0)) != 0) {
        if (bMsgFlag > 0) {
            ::TranslateMessage(&pMsg);
            ::DispatchMessageW(&pMsg);
        }
    }

    return static_cast<int>(pMsg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps = {};
    HDC hdc = {};

    switch (uMsg) {
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_ESCAPE:
            ::PostQuitMessage(0);
            break;
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;
    }

    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}
