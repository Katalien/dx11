#pragma once
#include "framework.h"

class Frustum {
public:
    Frustum(float screenDepth);
    ~Frustum() = default;
    bool CheckRectangle(float maxWidth, float maxHeight, float maxDepth, float minWidth, float minHeight, float minDepth);
    void BuildFrustum(XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

private:
    float screenDepth_;
    float planes_[6][4] = { {0}, {0}, {0}, {0}, {0}, {0} };
};
