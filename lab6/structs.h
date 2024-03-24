#pragma once

#include "camera.hpp"
#include "input.hpp"
#include <vector>
#include <windowsnumerics.h>
#include <windows.h>

struct Vertex {

    float x, y, z;
    float u, v;
};

struct WorldMatrixBuffer {
    XMMATRIX worldMatrix;
};

struct ViewMatrixBuffer {
    XMMATRIX viewProjectionMatrix;
};

struct SkyboxVertex {
    float x, y, z;
};

struct SkyboxWorldMatrixBuffer {
    XMMATRIX worldMatrix;
    XMFLOAT4 size;
};

struct SkyboxViewMatrixBuffer {
    XMMATRIX viewProjectionMatrix;
    XMFLOAT4 cameraPos;
};

struct TranspVertex {
    float x, y, z;
    COLORREF color;
};

struct BBRect {
    XMFLOAT3 v[4];
};

struct LIGHT {
    float4 lightPos;
    float4 lightColor;
};

