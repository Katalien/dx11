#pragma once

#include "camera.hpp"
#include "input.hpp"
#include "structs.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include "D3DInclude.h"
#include <string>
#include <iostream>
#include "Frustum.h"

#define MAX_LIGHT 10
#define SCREEN_NEAR 0.01f
#define SCREEN_FAR 100.0f

class Renderer {
public:
    static constexpr UINT defaultWidth = 1280;
    static constexpr UINT defaultHeight = 720;

    static Renderer& GetInstance();
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;

    bool Init(HINSTANCE hInstance, HWND hWnd);
    bool Render();
    bool Resize(UINT width, UINT height);

    void Cleanup();
    ~Renderer();

private:
    Renderer();

    HRESULT InitScene();
    void InputHandler();
    bool UpdateScene();
    void ProcessPostEffect(D3D11_VIEWPORT viewport);
    HRESULT InitRenderTexture(int textureWidth, int textureHeight);
    void ReleaseRenderTexture();

    ID3D11Device* pDevice_;
    ID3D11DeviceContext* pDeviceContext_;
    IDXGISwapChain* pSwapChain_;
    ID3D11RenderTargetView* pRenderTargetView_;

    ID3D11Buffer* pVertexBuffer_[3] = {NULL, NULL, NULL };
    ID3D11Buffer* pIndexBuffer_[3] = { NULL, NULL, NULL };
    ID3D11InputLayout* pInputLayout_[3] = { NULL, NULL, NULL };
    ID3D11VertexShader* pVertexShader_[3] = { NULL, NULL, NULL };
    ID3D11PixelShader* pPixelShader_[3] = { NULL, NULL, NULL };

    ID3D11Buffer* pGeomBufferInst_ = NULL;
    ID3D11Buffer* pPlanesWorldMatrixBuffer_[2] = { NULL, NULL };
    ID3D11Buffer* pSkyboxWorldMatrixBuffer_ = NULL;
    ID3D11Buffer* pViewMatrixBuffer_[2] = { NULL, NULL };
    ID3D11Buffer* pLightBuffer_ = NULL;
    ID3D11RasterizerState* pRasterizerState_;
    ID3D11SamplerState* pSampler_;

    ID3D11ShaderResourceView* pTexture_[3] = { NULL, NULL, NULL };

    ID3D11Texture2D* pDepthBuffer_;
    ID3D11DepthStencilView* pDepthBufferDSV_;
    ID3D11DepthStencilState* pDepthState_[2] = { NULL, NULL };
    ID3D11BlendState* pBlendState_;

    Camera* pCamera_;
    Input* pInput_;

    XMFLOAT4 rectVert[4];
    BBRect bb_rects[2];
    

    bool useNormalMap_ = true;
    bool showNormals_ = false;
    std::vector<Light> lights_;

    UINT width_;
    UINT height_;
    UINT numSphereTriangles_;
    float radius_;

    const TranspVertex VerticesT[4] = {
        {0, -1, -1},
        {0,  1, -1},
        {0,  1,  1},
        {0, -1,  1}
    };
    XMMATRIX TransparentMatrixs[2] = {
        DirectX::XMMatrixTranslation(1.8f, 0.0f, 0.0f),
        DirectX::XMMatrixTranslation(2.2f, 0.0f, 0.0f)
    };

    Frustum* pFrustum_;

    bool withPostEffect_ = true;
    bool withCulling_ = true;
    std::vector<Cube> cubes_;
    std::vector<int> cubeIndexies_;
    int cubesCount_ = 2;

    ID3D11VertexShader* pPostEffectVertexShader_ = NULL;
    ID3D11PixelShader* pPostEffectPixelShader_ = NULL;
    ID3D11SamplerState* pPostEffectSamplerState_ = NULL;
    ID3D11Buffer* pPostEffectConstantBuffer_ = NULL;
    ID3D11Texture2D* pRenderTargetTexture_ = NULL;
    ID3D11RenderTargetView* pPostEffectRenderTargetView_ = NULL;
    ID3D11ShaderResourceView* pShaderResourceView_ = NULL;
    
};