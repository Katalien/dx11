#pragma once
#include "utils.hpp"

class Renderer {
public:
    static Renderer& GetInstance();
    Renderer(Renderer&&) = delete;
    Renderer(const Renderer&) = delete;
    bool InitDevice(HWND hWnd);
    bool Rendering();
    bool ChangeSize(UINT width, UINT height);
    void CleanupDevice();

    static constexpr UINT WindowWidth = 720;
    static constexpr UINT WindowHeight = 720;

private:
    Renderer() {};
    HRESULT SetupBackBuffer();
    ID3D11Device* m_pDevice = nullptr;
    ID3D11DeviceContext* m_pContext = nullptr;
    IDXGISwapChain* m_pSwapChain = nullptr;
    ID3D11RenderTargetView* m_pBackBufferRTV = nullptr;
    UINT m_width = 0;
    UINT m_height = 0;
};