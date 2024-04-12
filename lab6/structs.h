#pragma once

#include "camera.hpp"
#include "input.hpp"
#include <vector>
#include <windowsnumerics.h>
#include <windows.h>

#define MAX_LIGHT 10
#define MAX_CUBE 30


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

struct GeomBuffer {
    XMMATRIX worldMatrix;
    XMMATRIX norm;
    XMFLOAT4 shineSpeedTexIdNM;
};

struct SceneBuffer {
    XMMATRIX viewProjectionMatrix;
    XMINT4 indexBuffer[MAX_CUBE];
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

struct TranspVertex {
    float x, y, z;
};

struct BBRect {
    XMFLOAT3 v[4];
};

struct Cube {
    XMFLOAT4 pos;
    XMFLOAT4 shineSpeedIdNM;
};

struct TransparentWorldMatrixBuffer {
    XMMATRIX worldMatrix;
    XMFLOAT4 color;
};

struct PostEffectConstantBuffer {
    XMINT4 params;
};