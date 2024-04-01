#include "SceneBuffer.h"

float3 ProcessLightColor(in float3 objectColor, in float3 objectNormal, in float3 position, in float shine, in bool transparent) {
    float3 finalColor = float3(0, 0, 0);

    if (lightParams.z > 0) {
        return float3(objectNormal * 0.5 + float3(0.5, 0.5, 0.5));
    }

    [unroll]
    for (int i = 0; i < lightParams.x; i++) {
        float3 norm = objectNormal;

        float3 lightDir = lights[i].lightPos.xyz - position;
        float lightDist = length(lightDir);
        lightDir /= lightDist;

        float atten = clamp(1.0 / (lightDist * lightDist), 0, 1);

        if (transparent && dot(lightDir, objectNormal) < 0.0) {
            norm = -norm;
        }
        finalColor += objectColor * max(dot(lightDir, norm), 0) * atten * lights[i].lightColor.xyz;

        float3 viewDir = normalize(cameraPos.xyz - position);
        float3 reflectDir = reflect(-lightDir, norm);
        float spec = shine > 0 ? pow(max(dot(viewDir, reflectDir), 0.0), shine.x) : 0.0;

        finalColor += objectColor * spec * lights[i].lightColor.xyz;
    }

    return finalColor;
}