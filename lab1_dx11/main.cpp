#include <directxcolors.h>
#include "rendering.hpp"
#include "utils.hpp"

using namespace DirectX;

HINSTANCE g_hInst = nullptr;

HRESULT Window(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                    _In_opt_ HINSTANCE hPrevInstance,
                    _In_ LPWSTR lpCmdLine,
                    _In_ int nCmdShow) {

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    if (FAILED(Window(hInstance, nCmdShow))) {
        return FALSE;
    }
    MSG msg = { 0 };
    Renderer& pRenderer = Renderer::GetInstance();
    bool exit = false;
    while (!exit) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (WM_QUIT == msg.message) {
            exit = true;
        }
        pRenderer.Rendering();
    }
    pRenderer.CleanupDevice();
    return (int)msg.wParam;
}

HRESULT Window(HINSTANCE hInstance, int nCmdShow) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"WindowClass";
    wcex.hIconSm = 0;
    if (!RegisterClassEx(&wcex)) {
        return FALSE;
    }
    g_hInst = hInstance;
    HWND hWnd = CreateWindow(L"WindowClass", 
                                L"Zinyakova", 
                                WS_OVERLAPPEDWINDOW, 
                                CW_USEDEFAULT, 
                                0, 
                                CW_USEDEFAULT, 
                                0, 
                                nullptr,
                                nullptr, 
                                hInstance, 
                                nullptr);

    if (!hWnd) {
        return FALSE;
    }
    Renderer& pRenderer = Renderer::GetInstance();
    if (!pRenderer.InitDevice(hWnd)) {
        return FALSE;
    }

    RECT rc;
    rc.left = 0;
    rc.right = pRenderer.WindowWidth;
    rc.top = 0;
    rc.bottom = pRenderer.WindowHeight;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);
    MoveWindow(hWnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    if (message == WM_SIZE) {
        RECT rc;
        GetClientRect(hWnd, &rc);
        Renderer::GetInstance().ChangeSize(rc.right - rc.left, rc.bottom - rc.top);
    }
    if (message == WM_PAINT) {
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    if (message == WM_DESTROY) {
        PostQuitMessage(0);
    }
    else { 
        return DefWindowProc(hWnd, message, wParam, lParam); 
    }
    return 0;
}