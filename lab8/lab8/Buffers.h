#include "Macros.h"
#include "LightCalc.h"

struct GeomBuffer {
    float4x4 worldMatrix;
    float4x4 norm;
    float4 shineSpeedTexIdNM;
};

cbuffer GeomBufferInst : register (b0) {
    GeomBuffer geomBuffer[MAX_CUBE];
};

cbuffer SceneConstantBuffer : register (b1) {
    float4x4 viewProjectionMatrix;
    float4 planes[6];
};

cbuffer IndexBuffer : register(b2) {
    uint4 objectIDs[MAX_CUBE];
};