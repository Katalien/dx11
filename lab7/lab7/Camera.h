#pragma once

#include "framework.h"

class Camera {
public:
    Camera();
    void Rotate(float dphi, float dtheta);

    XMMATRIX& GetViewMatrix() {
        return viewMatrix_;
    };

    XMFLOAT3& GetPosition() {
        return position_;
    };
private:
    XMMATRIX viewMatrix_;
    XMFLOAT3 focus_;
    XMFLOAT3 position_;
    float r_;
    float theta_;
    float phi_;

    void UpdateViewMatrix();
};