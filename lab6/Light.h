#define SCREEN_NEAR 0.01f
#define SCREEN_FAR 100.0f
#define MAX_LIGHT 60

struct LIGHT {
    float4 lightPos;
    float4 lightColor;
};

cbuffer LightBuffer : register (b2) {
    float4 cameraPos;
    int4 lightParams;
    LIGHT lights[MAX_LIGHT];
    float4 ambientColor;
};