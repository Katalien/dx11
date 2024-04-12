#pragma once

#include "camera.h"
#include "input.h"
#include <vector>
#include <windowsnumerics.h>
#include <windows.h>
#include "Macros.h"

struct Light {
    XMFLOAT4 pos;
    XMFLOAT4 color;
};

struct Cube {
    XMFLOAT4 pos;
    XMFLOAT4 shineSpeedIdNM;
};

struct PostEffectConstantBuffer {
    XMINT4 params;
};

struct Vertex {
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT3 normal;
    XMFLOAT3 tangent;
};

struct GeomBuffer {
    XMMATRIX worldMatrix;
    XMMATRIX norm;
    XMFLOAT4 shineSpeedTexIdNM;
};

struct SceneBuffer {
    XMMATRIX viewProjectionMatrix;
    XMFLOAT4 planes[6];
};


struct LightBuffer {
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

struct BBRect {
    XMFLOAT3 v[4];
};

struct TransparentVertex {
    float x, y, z;
};

struct TransparentWorldMatrixBuffer {
    XMMATRIX worldMatrix;
    XMFLOAT4 color;
};