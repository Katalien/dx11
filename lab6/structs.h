#pragma once

#include "camera.hpp"
#include "input.hpp"
#include <vector>
#include <windowsnumerics.h>
#include <windows.h>

#define MAX_LIGHT 10

struct Light {
    XMFLOAT4 pos;
    XMFLOAT4 color;
};

struct Vertex {
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT3 normal;
    XMFLOAT3 tangent;
};

struct WorldMatrixBuffer {
    XMMATRIX worldMatrix;
    XMFLOAT4 shine;
};

struct ViewMatrixBuffer {
    XMMATRIX viewProjectionMatrix;
    XMFLOAT4 cameraPos;
    XMINT4 lightParams;
    Light lights[MAX_LIGHT];
    XMFLOAT4 ambientColor;
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

