#pragma once
#pragma comment(lib,"d3dcompiler")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <directxmath.h>
#include <string>
#include "Vertex.hpp"

using namespace DirectX;


class Renderer {
public:
    bool InitDevice(HWND hWnd);
    bool Resize(UINT width, UINT height);
    void Cleanup();
    bool Render();

private:
    HRESULT InitScene();
    HRESULT SetupBackBuffer();
    
    ID3D11Device* m_pDevice = nullptr;
    ID3D11DeviceContext* m_pContext = nullptr;
    IDXGISwapChain* m_pSwapChain = nullptr;
    ID3D11RenderTargetView* m_pBackBufferRTV = nullptr;
    UINT m_width = 0;
    UINT m_height = 0;
    ID3D11Buffer* m_pVertexBuffer = nullptr;
    ID3D11Buffer* m_pIndexBuffer = nullptr;
    ID3D11InputLayout* m_pInputLayout = nullptr;
    ID3D11VertexShader* m_pVertexShader = nullptr;
    ID3D11PixelShader* m_pPixelShader = nullptr;
};